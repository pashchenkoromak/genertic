#include "world.hpp"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>

World::World()
{
  int n = 30;
  int m = 30;
  m_vecUnits.resize(n);
  for (int i = 0; i < n; i++) {
    m_vecUnits[i].reserve(m);
    for (int j = 0; j < m; j++) {
      if (rand() % 5 == 0)
        m_vecUnits[i].push_back(
          unitInWorld(std::make_shared<Unit>(), std::make_pair(i, j)));
      else
        m_vecUnits[i].push_back(unitInWorld(
          std::make_shared<Unit>(Unit::NO_UNIT()), std::make_pair(i, j)));
    }
  }
}

void
World::getNextMove()
{
  for (auto row : m_vecUnits)
    for (auto unit : row)
      if (*unit.unit != Unit::NO_UNIT())
        handleOperation(unit.unit->nextMove(), unit);
}

void
World::handleOperation(const Operation& operation, unitInWorld& unit)
{
  unit.unit->changeEnergy(-unit.unit->getAge() / 100);
  switch (operation.type) {
    case GO:
      go(unit, operation.params[0]);
      break;
    case SEE:
      see(unit, operation.params[0]);
      break;
    case WAIT:
      wait(unit);
      break;
    case DIE:
      kill(unit);
      break;
    case MAKE_CHILD:
      makeChild(unit);
      break;
    case PHOTOSYNTESIS:
      photosintes(unit);
      break;
    default:
      wait(unit);
  }
}
void
World::go(unitInWorld& unit, const std::string& direction)
{
  auto newPos = getNewPos(unit.pos, direction);
  if (canGo(newPos)) {
    std::swap(m_vecUnits[newPos.first][newPos.second],
              m_vecUnits[unit.pos.first][unit.pos.second]);
    unit.pos = newPos;
  }
}

void
World::see(unitInWorld& unit, const std::string& direction)
{
  auto newPos = getNewPos(unit.pos, direction);
  if (*(unit.unit) == Unit::NO_UNIT())
    unit.unit->setAnswer(answer::Empty);
  else
    unit.unit->setAnswer(answer::UnitIsHere);
}

void
World::wait(unitInWorld& unit)
{
  unit.unit->changeEnergy(-1);
}

void
World::kill(unitInWorld& unit)
{
  *unit.unit = Unit::NO_UNIT();
}

void
World::makeChild(unitInWorld& unit)
{
  unit.unit->changeEnergy(-ENERGY_FOR_CHILD);
  for (size_t i = 0; i < 9; i++) {
    auto newPos = findPlace(unit.pos);
    if (newPos == NULL_POS)
      return;
    m_vecUnits[newPos.first][newPos.second] =
      unitInWorld(std::make_shared<Unit>(*unit.unit), newPos);
    if (rand() % 10000 < MUTATION_PROBABILITY * 10000)
      m_vecUnits[newPos.first][newPos.second].unit->mutation();
  }
}
bool
World::canGo(const std::pair<size_t, size_t>& newPos)
{
  if (newPos.first >= m_vecUnits.size() ||
      newPos.second >= m_vecUnits[0].size())
    return false;
  return (*m_vecUnits[newPos.first][newPos.second].unit == Unit::NO_UNIT());
}

void
World::photosintes(unitInWorld& unit)
{
  unit.unit->changeEnergy(unit.pos.first / 10);
}

std::pair<size_t, size_t>
World::getNewPos(const std::pair<size_t, size_t>& pos,
                 const std::string& direction)
{
  std::pair<size_t, size_t> newPos = pos;
  if (direction == directionToString(directions::LEFT))
    newPos.second--;
  if (direction == directionToString(directions::RIGHT))
    newPos.second++;
  if (direction == directionToString(directions::UP))
    newPos.first--;
  if (direction == directionToString(directions::DOWN))
    newPos.first++;
  if (direction == directionToString(directions::UP_LEFT)) {
    newPos.first--;
    newPos.second--;
  }
  if (direction == directionToString(directions::UP_RIGHT)) {
    newPos.first--;
    newPos.second++;
  }
  if (direction == directionToString(directions::DOWN_LEFT)) {
    newPos.first++;
    newPos.second--;
  }
  if (direction == directionToString(directions::DOWN_RIGHT)) {
    newPos.first++;
    newPos.second++;
  }
  newPos.first = (newPos.first + m_vecUnits.size()) % m_vecUnits.size();
  newPos.second = (newPos.first + m_vecUnits[0].size()) % m_vecUnits[0].size();
}

std::pair<size_t, size_t>
World::findPlace(const std::pair<size_t, size_t>& pos)
{
  for (int i = -1; i <= 1; i++)
    for (int j = -1; j <= 1; j++)
      if (canGo(std::make_pair(pos.first + i, pos.second + j)))
        return std::make_pair(pos.first + i, pos.second + j);
  return NULL_POS;
}

size_t
World::getNumberOfAlives()
{
  size_t result = 0;
  for (auto row : m_vecUnits)
    for (auto unit : row) {
      if (*unit.unit != Unit::NO_UNIT())
        result++;
    }
  return result;
}

void
World::show() const
{
  long long sumEnergy = 0;
  for (auto row : m_vecUnits) {
    for (auto unit : row) {
      if (*unit.unit == Unit::NO_UNIT())
        std::cout << " .";
      else {
        std::cout << " x";
        sumEnergy += unit.unit->getEnergy();
      }
    }
    std::cout << std::endl;
  }
  std::cout << sumEnergy << std::endl;
}
