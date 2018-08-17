#include "genom.hpp"

Genom::Genom() {
  m_genom.resize(Genom::DEFAULT_SIZE);
  for (size_t i = 0; i < Genom::DEFAULT_SIZE; i++) m_genom[i] = rand() % 2;
}

void Genom::mutation() {
  size_t index = rand() % (m_genom.size());
  m_genom[index] = 1 - index;
}

Operation Genom::nextMove(long long& energy) {
  Operation doNow;
  while (!doNow.isWorldOperation() && energy > 0) {
    operationType type =
        static_cast<operationType>(getNextOperation(m_nextMoveNum));
    m_nextMoveNum += CommandLength::OPERATION;
    doNow.type = type;
    switch (type) {
      case GOTO:
        m_nextMoveNum += parseGoto();
        break;
      case PHOTOSYNTESIS:
        doNow.type = operationType::PHOTOSYNTESIS;
        break;
      case WAIT:
        break;
      case GO:
        parseGo();
        break;
      case IF:
        parseIf(energy);
        break;
      default:
        doNow.type = operationType::PHOTOSYNTESIS;
    }
    energy--;
  }
  if (energy)
    return doNow;
  else
    return operationType::DIE;
}

long long Genom::parseGoto() {
  size_t length = 0;
  for (size_t i = m_nextMoveNum + CommandLength::OPERATION;
       i < m_nextMoveNum + CommandLength::OPERATION + CommandLength::GOTO;
       i++) {
    length = length * 2 + m_genom[i];
  }
  size_t where = 0;
  for (size_t i =
           m_nextMoveNum + CommandLength::OPERATION + CommandLength::GOTO;
       i <
       m_nextMoveNum + CommandLength::OPERATION + CommandLength::GOTO + length;
       i++) {
    where = where * 2 + m_genom[i];
  }
  return where;
}

Operation Genom::parseGo() {
  size_t direction = 0;
  for (size_t i = m_nextMoveNum + CommandLength::OPERATION;
       i < m_nextMoveNum + CommandLength::OPERATION + CommandLength::DIRECTION;
       i++) {
    direction = direction * 2 + m_genom[i];
  }
  Operation doNow;
  doNow.params.push_back(directionToString(static_cast<directions>(direction)));
  return doNow;
}

long long Genom::parseIf(long long& energy) {
  bool condition = parseBoolExpression(m_nextMoveNum, energy, m_nextMoveNum);
  if (condition)
    m_nextMoveNum = parseGoto();
  else {
    m_nextMoveNum += CommandLength::GOTO;
    m_nextMoveNum = parseGoto();
  }
}

size_t Genom::getNextOperation(const size_t startCommand,
                               const size_t commandLength) {
  auto command = startCommand % m_genom.size();
  auto first = m_genom.begin() + command;
  auto last = m_genom.begin() + command + commandLength;
  std::vector<char> subVec(first, last);
  return Operation::parseOperationType(subVec);
}

int Genom::parseExpression(const size_t startCommand, long long& energy,
                           size_t& next) {
  next %= m_genom.size();
  energy--;
  if (energy <= 0) return 0;
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
      result = lhs % rhs;
      break;
    default:
      break;
  }
  return result;
}

bool Genom::parseBoolExpression(const size_t startCommand, long long& energy,
                                size_t& next) {
  energy--;
  if (energy <= 0) return false;
  int lhs, rhs;
  bool b_lhs, b_rhs, value;
  bool result = false;
  next = startCommand + CommandLength::BOOL;
  boolMath nextCommand = static_cast<boolMath>(
      getNextOperation(startCommand, CommandLength::BOOL));
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
      result = (lhs && rhs);
      break;
    case OR:
      b_lhs = parseBoolExpression(next, energy, next);
      b_rhs = parseBoolExpression(next, energy, next);
      result = (lhs || rhs);
      break;
    case NO:
      value = parseBoolExpression(next, energy, next);
      result = (!value);
      break;
    case XOR:
      b_lhs = parseBoolExpression(next, energy, next);
      b_rhs = parseBoolExpression(next, energy, next);
      result = (lhs ^ rhs);
      break;
    case ANSWER:
      result = getNextOperation(next, CommandLength::ANSWER);
      next += CommandLength::ANSWER;
    case BOOL_CONST:
      result = getNextOperation(next, CommandLength::CONST_BOOL);
      next += CommandLength::CONST_BOOL;
    default:
      result = false;
      break;
  }
  return result;
}
