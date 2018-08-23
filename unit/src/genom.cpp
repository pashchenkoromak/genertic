#include "genom.hpp"
#include <iostream>
Genom::Genom()
{
  std::vector<char> append;
  for (; m_genom.size() < Genom::DEFAULT_SIZE;) {
    if (rand() % 50 == 0)
      append = intToChar(operationType::MAKE_CHILD, CommandLength::OPERATION);
    else
      append =
        intToChar(rand() % operationType::TYPE_COUNT, CommandLength::OPERATION);
    m_genom.insert(m_genom.end(), append.begin(), append.end());
  }
}

void
Genom::mutation()
{
  size_t mutationType = rand() % 100;
  std::vector<size_t> probabilities{ 30, 90, 100 };
  if (mutationType < probabilities[0])
    genomMutation();
  else if (mutationType < probabilities[1])
    genMutation();
  else
    chromosomeMutation();
}

Operation
Genom::nextMove(long long energy)
{
  if (rand() % 10000 == 0)
    mutation();
  Operation doNow;
  do {
    operationType type =
      static_cast<operationType>(getNextOperation(m_nextMoveNum));
    m_nextMoveNum = (m_nextMoveNum + CommandLength::OPERATION) % m_genom.size();
    doNow.type = type;
    switch (type) {
      case GOTO:
        m_nextMoveNum = parseGoto(m_nextMoveNum) % m_genom.size();
        break;
      case PHOTOSYNTESIS:
        doNow.type = operationType::PHOTOSYNTESIS;
        break;
      case TILL:
        doNow.type = operationType::TILL;
        break;
      case WAIT:
        doNow.type = operationType::WAIT;
        break;
      case GO:
        doNow = parseGo();
        break;
      case SEE:
        doNow = parseSee();
        break;
      case IF:
        m_nextMoveNum = parseIf(energy) % m_genom.size();
        break;
      case MAKE_CHILD:
        doNow = parseMakeChild();
        break;
      case ATTACK:
        doNow = parseAttack();
        break;
    }
    energy--;
  } while (!doNow.isWorldOperation() && energy > 0);
  if (energy >= 0)
    return doNow;
  else
    return operationType::DIE;
}

void
Genom::genomMutation()
{
  const size_t countNewGenes = rand() % 5;
  const size_t n = m_genom.size();
  m_genom.resize(m_genom.size() + countNewGenes);
  for (size_t i = n - 1; i < m_genom.size(); i++)
    m_genom[i] = rand() % 2;
}

void
Genom::genMutation()
{
  const size_t n = m_genom.size();
  const size_t begin = rand() % n;
  const size_t length = rand() % 10;
  for (int i = 0; i < length; i++)
    m_genom[(begin + i) % n] = rand() % 2;
}

void
Genom::chromosomeMutation()
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

void
Genom::doubleGen()
{
  const size_t n = m_genom.size();
  const size_t begin = rand() % n;
  const size_t length = rand() % 10;

  /* no subvector algo as it says here
     https://stackoverflow.com/questions/421573/best-way-to-extract-a-subvector-from-a-vector
     because of cycle nature of genom std::vector<char> adding(length);
  */
  std::vector<char> adding(length);
  for (size_t i = 0; i < length; i++)
    adding[i] = m_genom[(begin + i) % n];
  auto it = m_genom.begin() + (begin + length) % n;
  m_genom.insert(it, adding.begin(), adding.end());
}

void
Genom::eraseGen()
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

void
Genom::reverseGen()
{
  const size_t n = m_genom.size();
  const size_t begin = rand() % n;
  const size_t length = rand() % 10;
  for (size_t i = 0; i < length; i++) {
    std::swap(m_genom[(begin + i) % n], m_genom[(begin + length - i - 1) % n]);
  }
}

long long
Genom::parseGoto(const long long startPosition)
{
  size_t where = 0, n = m_genom.size();
  for (size_t i = 0; i < CommandLength::GOTO; i++) {
    where = where * 2 + m_genom[(startPosition + i) % n];
  }
  return where;
}

Operation
Genom::parseGo()
{
  size_t direction = getNextOperation(m_nextMoveNum, CommandLength::DIRECTION);
  Operation doNow;
  doNow.type = operationType::GO;
  doNow.params.push_back(direction);
  return doNow;
}

Operation
Genom::parseMakeChild()
{
  Operation doNow;
  size_t child_count =
    getNextOperation(m_nextMoveNum, CommandLength::CHILD_COUNT);
  doNow.type = operationType::MAKE_CHILD;
  doNow.params.push_back(child_count);
  return doNow;
}

Operation
Genom::parseSee()
{
  Operation doNow = parseGo();
  doNow.type = operationType::SEE;
  return doNow;
}

Operation
Genom::parseAttack()
{
  Operation doNow = parseGo();
  doNow.type = operationType::ATTACK;
  return doNow;
}

long long
Genom::parseIf(long long& energy)
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

size_t
Genom::getNextOperation(const size_t startCommand, const size_t commandLength)
{
  size_t n = m_genom.size();
  std::vector<char> nextOperation(commandLength);
  for (size_t i = 0; i < commandLength; i++)
    nextOperation[i] = m_genom[(startCommand + i) % n];

  return Operation::parseOperationType(nextOperation);
}

/*
 * Expression = <exp>
 * <exp> = <maths operation> <exp> <exp>
 * <exp> = <const>
 *
 *  So parsing is here
 */
int
Genom::parseExpression(const size_t startCommand,
                       long long& energy,
                       size_t& next)
{
  next %= m_genom.size();
  energy--;
  if (energy <= 0)
    return 0;
  int lhs, rhs;
  int result = 0;
  next = startCommand + CommandLength::MATH;
  maths nextCommand =
    static_cast<maths>(getNextOperation(startCommand, CommandLength::MATH));
  switch (nextCommand) {
    case NUMBER_CONST:
      result = getNextOperation(next, CommandLength::NUMBER);
      next += CommandLength::NUMBER;
      break;
    case PLUS:
      lhs = parseExpression(next, energy, next);
      rhs = parseExpression(next, energy, next);
      result = lhs + rhs;
      break;
    case MINUS:
      lhs = parseExpression(next, energy, next);
      rhs = parseExpression(next, energy, next);
      result = lhs - rhs;
      break;
    case ENERGY:
      result = energy;
      break;
    case MULTIPLE:
      lhs = parseExpression(next, energy, next);
      rhs = parseExpression(next, energy, next);
      result = lhs * rhs;
      break;
    case DIVIDE:
      lhs = parseExpression(next, energy, next);
      rhs = parseExpression(next, energy, next);
      if (rhs == 0)
        result = 0;
      else
        result = lhs / rhs;
      break;
    case REST_DEVIDE:
      lhs = parseExpression(next, energy, next);
      rhs = parseExpression(next, energy, next);
      if (rhs == 0)
        result = 0;
      else
        result = lhs % rhs;
      break;
    case ANSWER:
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
bool
Genom::parseBoolExpression(const size_t startCommand,
                           long long& energy,
                           size_t& next)
{
  energy--;
  if (energy <= 0)
    return false;
  int lhs, rhs;
  bool b_lhs, b_rhs, value;
  bool result = false;
  next = startCommand + CommandLength::BOOL;
  boolMath nextCommand =
    static_cast<boolMath>(getNextOperation(startCommand, CommandLength::BOOL));
  switch (nextCommand) {
    case MORE:
      lhs = parseExpression(next, energy, next);
      rhs = parseExpression(next, energy, next);
      result = (lhs > rhs);
      break;
    case MORE_EQUAL:
      lhs = parseExpression(next, energy, next);
      rhs = parseExpression(next, energy, next);
      result = (lhs >= rhs);
      break;
    case LESS:
      lhs = parseExpression(next, energy, next);
      rhs = parseExpression(next, energy, next);
      result = (lhs < rhs);
      break;
    case LESS_EQUAL:
      lhs = parseExpression(next, energy, next);
      rhs = parseExpression(next, energy, next);
      result = (lhs <= rhs);
      break;
    case EQUAL:
      lhs = parseExpression(next, energy, next);
      rhs = parseExpression(next, energy, next);
      result = (lhs == rhs);
      break;
    case NO_EQUAL:
      lhs = parseExpression(next, energy, next);
      rhs = parseExpression(next, energy, next);
      result = (lhs != rhs);
      break;
    case AND:
      b_lhs = parseBoolExpression(next, energy, next);
      b_rhs = parseBoolExpression(next, energy, next);
      result = (b_lhs && b_rhs);
      break;
    case OR:
      b_lhs = parseBoolExpression(next, energy, next);
      b_rhs = parseBoolExpression(next, energy, next);
      result = (b_lhs || b_rhs);
      break;
    case NO:
      value = parseBoolExpression(next, energy, next);
      result = (!value);
      break;
    case XOR:
      b_lhs = parseBoolExpression(next, energy, next);
      b_rhs = parseBoolExpression(next, energy, next);
      result = (b_lhs ^ b_rhs);
      break;
    case BOOL_CONST:
      result = getNextOperation(next, CommandLength::CONST_BOOL);
      next += CommandLength::CONST_BOOL;
      break;
    default:
      result = false;
      break;
  }
  return result;
}
