#include "genom.hpp"
#include <iostream>
Genom::Genom()
{
    std::vector<char> append;
    for (; m_genom.size() < Genom::DEFAULT_SIZE;) {
        if (rand() % 50 == 0)
            append = intToChar(static_cast<int>(operationType::MAKE_CHILD), CommandLength::OPERATION);
        else
            append = intToChar(rand() % static_cast<int>(operationType::TYPE_COUNT), CommandLength::OPERATION);
        m_genom.insert(m_genom.end(), append.begin(), append.end());
    }
}

void Genom::mutation()
{
    size_t mutationType = rand() % 100;
    std::vector<size_t> probabilities{30, 90, 100};
    if (mutationType < probabilities[0])
        genomMutation();
    else if (mutationType < probabilities[1])
        genMutation();
    else
        chromosomeMutation();
}

Operation Genom::nextMove(long long& energy, bool canMutate /* = true */)
{
    if (canMutate && rand() % 10000 == 0) {
        mutation();
    }
    Operation doNow;
    while (energy >= 0 && !doNow.isWorldOperation()) {
        operationType type = static_cast<operationType>(getNextOperation(m_nextMoveNum));
        m_nextMoveNum = (m_nextMoveNum + CommandLength::OPERATION) % m_genom.size();
        doNow.type = type;
        switch (type) {
            case operationType::GOTO:
                m_nextMoveNum = parseGoto(m_nextMoveNum) % m_genom.size();
                break;
            case operationType::PHOTOSYNTESIS:
                doNow.type = operationType::PHOTOSYNTESIS;
                break;
            case operationType::TILL:
                doNow.type = operationType::TILL;
                break;
            case operationType::WAIT:
                doNow.type = operationType::WAIT;
                break;
            case operationType::GO:
                doNow = parseGo();
                break;
            case operationType::SEE:
                doNow = parseSee();
                break;
            case operationType::IF:
                m_nextMoveNum = parseIf(energy) % m_genom.size();
                break;
            case operationType::MAKE_CHILD:
                doNow = parseMakeChild();
                break;
            case operationType::ATTACK:
                doNow = parseAttack();
                break;
        }
        energy--;
    }
    if (energy >= 0)
        return doNow;
    else {
        energy = 0;
        return operationType::DIE;
    }
}

void Genom::genomMutation()
{
    const size_t countNewGenes = rand() % 5;
    const size_t n = m_genom.size();
    m_genom.resize(m_genom.size() + countNewGenes);
    for (size_t i = n - 1; i < m_genom.size(); i++) {
        m_genom[i] = rand() % 2;
    }
}

void Genom::genMutation()
{
    const size_t n = m_genom.size();
    const size_t begin = rand() % n;
    const size_t length = rand() % 10;
    for (int i = 0; i < length; i++) {
        m_genom[(begin + i) % n] = rand() % 2;
    }
}

void Genom::chromosomeMutation()
{
    const size_t mutationType = rand() % 3;
    switch (mutationType) {
        case 0:
            doubleGen();
            break;
        case 1:
            eraseGen();
            break;
        case 2:
            reverseGen();
            break;
    }
}

void Genom::doubleGen()
{
    const size_t n = m_genom.size();
    const size_t begin = rand() % n;
    const size_t length = rand() % 10;

    /* no subvector algo as it says here
       https://stackoverflow.com/questions/421573/best-way-to-extract-a-subvector-from-a-vector
       because of cycle nature of genom std::vector<char> adding(length);
    */
    std::vector<char> adding(length);
    for (size_t i = 0; i < length; i++) {
        adding[i] = m_genom[(begin + i) % n];
    }
    auto it = m_genom.begin() + (begin + length) % n;
    m_genom.insert(it, adding.begin(), adding.end());
}

void Genom::eraseGen()
{
    const size_t n = m_genom.size();
    const size_t begin = rand() % n;
    const size_t length = rand() % 10;
    if (begin + length < n)
        m_genom.erase(m_genom.begin() + begin, m_genom.begin() + begin + length);
    else {
        m_genom.erase(m_genom.begin() + begin, m_genom.end());
        m_genom.erase(m_genom.begin(), m_genom.begin() + length - (n - begin));
    }
}

void Genom::reverseGen()
{
    const size_t n = m_genom.size();
    const size_t begin = rand() % n;
    const size_t length = rand() % 10;
    for (size_t i = 0; i < length; i++) {
        std::swap(m_genom[(begin + i) % n], m_genom[(begin + length - i - 1) % n]);
    }
}

long long Genom::parseGoto(const long long startPosition)
{
    size_t where = 0, n = m_genom.size();
    for (size_t i = 0; i < CommandLength::GOTO; i++) {
        where = where * 2 + m_genom[(startPosition + i) % n];
    }
    return where;
}

Operation Genom::parseGo()
{
    size_t direction = 0, n = m_genom.size();
    for (size_t i = 0; i < CommandLength::DIRECTION; i++) {
        direction = direction * 2 + m_genom[(m_nextMoveNum + i) % n];
    }
    Operation doNow;
    doNow.type = operationType::GO;
    doNow.params.push_back(directionToString(static_cast<directions>(direction)));
    return doNow;
}

Operation Genom::parseMakeChild()
{
    Operation doNow;
    doNow.type = operationType::MAKE_CHILD;
    return doNow;
}

Operation Genom::parseSee()
{
    Operation doNow = parseGo();
    doNow.type = operationType::SEE;
    return doNow;
}

Operation Genom::parseAttack()
{
    Operation doNow = parseGo();
    doNow.type = operationType::ATTACK;
    return doNow;
}

long long Genom::parseIf(long long& energy)
{
    size_t next = m_nextMoveNum;
    bool condition = parseBoolExpression(next, energy, next);
    if (condition)
        next = parseGoto(next);
    else {
        next += CommandLength::GOTO;
        next = parseGoto(next);
    }
    return next;
}

size_t Genom::getNextOperation(const size_t startCommand, const size_t commandLength)
{
    auto command = startCommand % m_genom.size();
    auto first = m_genom.begin() + command;
    auto last = m_genom.begin() + command + commandLength;
    std::vector<char> subVec(first, last);
    return static_cast<size_t>(Operation::parseOperationType(subVec));
}

/*
 * Expression = <exp>
 * <exp> = <maths operation> <exp> <exp>
 * <exp> = <const>
 *
 *  So parsing is here
 */
int Genom::parseExpression(const size_t startCommand, long long& energy, size_t& next)
{
    next %= m_genom.size();
    energy--;
    if (energy <= 0) {
        return 0;
    }
    int lhs, rhs;
    int result = 0;
    next = startCommand + CommandLength::MATH;
    maths nextCommand = static_cast<maths>(getNextOperation(startCommand, CommandLength::MATH));
    switch (nextCommand) {
        case maths::NUMBER_CONST:
            result = getNextOperation(next, CommandLength::NUMBER);
            next += CommandLength::NUMBER;
            break;
        case maths::PLUS:
            lhs = parseExpression(next, energy, next);
            rhs = parseExpression(next, energy, next);
            result = lhs + rhs;
            break;
        case maths::MINUS:
            lhs = parseExpression(next, energy, next);
            rhs = parseExpression(next, energy, next);
            result = lhs - rhs;
            break;
        case maths::ENERGY:
            result = energy;
            break;
        case maths::MULTIPLE:
            lhs = parseExpression(next, energy, next);
            rhs = parseExpression(next, energy, next);
            result = lhs * rhs;
            break;
        case maths::DIVIDE:
            lhs = parseExpression(next, energy, next);
            rhs = parseExpression(next, energy, next);
            if (rhs == 0)
                result = 0;
            else
                result = lhs / rhs;
            break;
        case maths::REST_DEVIDE:
            lhs = parseExpression(next, energy, next);
            rhs = parseExpression(next, energy, next);
            if (rhs == 0)
                result = 0;
            else
                result = lhs % rhs;
            break;
        case maths::ANSWER:
            result = getNextOperation(next, CommandLength::ANSWER);
            next += CommandLength::ANSWER;
            break;
        default:
            break;
    }
    return result;
}

/*
 * BoolExpression = <Bexp>
 * <Bexp> = <bool operation> <Bexp> <Bexp>
 * <Bexp> = <bool const>
 *
 *  So parsing is here
 */
bool Genom::parseBoolExpression(const size_t startCommand, long long& energy, size_t& next)
{
    energy--;
    if (energy <= 0) {
        return false;
    }
    int lhs, rhs;
    bool b_lhs, b_rhs, value;
    bool result = false;
    next = startCommand + CommandLength::BOOL;
    boolMath nextCommand = static_cast<boolMath>(getNextOperation(startCommand, CommandLength::BOOL));
    switch (nextCommand) {
        case boolMath::MORE:
            lhs = parseExpression(next, energy, next);
            rhs = parseExpression(next, energy, next);
            result = (lhs > rhs);
            break;
        case boolMath::MORE_EQUAL:
            lhs = parseExpression(next, energy, next);
            rhs = parseExpression(next, energy, next);
            result = (lhs >= rhs);
            break;
        case boolMath::LESS:
            lhs = parseExpression(next, energy, next);
            rhs = parseExpression(next, energy, next);
            result = (lhs < rhs);
            break;
        case boolMath::LESS_EQUAL:
            lhs = parseExpression(next, energy, next);
            rhs = parseExpression(next, energy, next);
            result = (lhs <= rhs);
            break;
        case boolMath::EQUAL:
            lhs = parseExpression(next, energy, next);
            rhs = parseExpression(next, energy, next);
            result = (lhs == rhs);
            break;
        case boolMath::NO_EQUAL:
            lhs = parseExpression(next, energy, next);
            rhs = parseExpression(next, energy, next);
            result = (lhs != rhs);
            break;
        case boolMath::AND:
            b_lhs = parseBoolExpression(next, energy, next);
            b_rhs = parseBoolExpression(next, energy, next);
            result = (b_lhs && b_rhs);
            break;
        case boolMath::OR:
            b_lhs = parseBoolExpression(next, energy, next);
            b_rhs = parseBoolExpression(next, energy, next);
            result = (b_lhs || b_rhs);
            break;
        case boolMath::NO:
            value = parseBoolExpression(next, energy, next);
            result = (!value);
            break;
        case boolMath::XOR:
            b_lhs = parseBoolExpression(next, energy, next);
            b_rhs = parseBoolExpression(next, energy, next);
            result = (b_lhs ^ b_rhs);
            break;
        case boolMath::BOOL_CONST:
            result = getNextOperation(next, CommandLength::CONST_BOOL);
            next += CommandLength::CONST_BOOL;
            break;
        default:
            result = false;
            break;
    }
    return result;
}
