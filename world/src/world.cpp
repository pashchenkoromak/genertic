#include "world.hpp"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>

World::World()
  : sun(std::make_shared<IUnit>(INT32_MAX))
{
  int n = 20;
  int m = 30;
  m_vecUnits.resize(n);
  m_earthEnergy.resize(n);
  for (int i = 0; i < n; i++) {
    m_vecUnits[i].reserve(m);
    m_earthEnergy[i].reserve(m);
    for (int j = 0; j < m; j++) {
      m_earthEnergy[i][j] = std::make_shared<IUnit>(rand() % 1000);
      if (rand() % 10000 <= FULLNESS * 10000)
        m_vecUnits[i].push_back(unitInWorld(
          std::make_shared<Unit>(rand() % 1000), std::make_pair(i, j)));
      else
        m_vecUnits[i].push_back(
          unitInWorld(IUnit::NO_UNIT(), std::make_pair(i, j)));
    }
  }
}

void
World::getNextMove()
{
  childrenCount = bornCount = 0;
  for (auto row : m_vecUnits)
    for (auto unit : row)
      if (!unit.unit->isNo_Unit() && !unit.unit->isCorpse())
        handleOperation(unit.unit->nextOperation(), unit);
      else {
        if (unit.unit->isCorpse())
          m_earthEnergy[unit.pos.first][unit.pos.second]->changeEnergy(
            unit.unit, std::max(3ll, CORPSE_ENERGY * 2 / 3));
        if (unit.unit->getEnergy() <= 0)
          clean(unit);
      }
}

void
World::handleOperation(const Operation& operation, unitInWorld& unit)
{
  sun->changeEnergy(unit.unit, unit.unit->getAge() * AGE_PENALTY);
  switch (operation.type) {
    case GO:
      go(unit, static_cast<directions>(operation.params[0]));
      break;
    case SEE:
      see(unit, static_cast<directions>(operation.params[0]));
      break;
    case WAIT:
      wait(unit);
      break;
    case DIE:
      kill(unit);
      break;
    case MAKE_CHILD:
      makeChild(unit, operation.params[0]);
      break;
    case PHOTOSYNTESIS:
      photosynthesis(unit);
      break;
    case TILL:
      till(unit);
      break;
    case ATTACK:
      attack(unit, static_cast<directions>(operation.params[0]));
      break;
    default:
      wait(unit);
  }
}
void
World::go(unitInWorld& unit, const directions direction)
{
  auto newPos = getNewPos(unit.pos, direction);
  if (canGo(newPos)) {
    std::swap(m_vecUnits[newPos.first][newPos.second],
              m_vecUnits[unit.pos.first][unit.pos.second]);
    unit.pos = newPos;
  }
}

void
World::attack(unitInWorld& attacker, const directions direction)
{
  attacks++;
  auto newPos = getNewPos(attacker.pos, direction);
  if (canAttack(newPos)) {
    size_t x = newPos.first, y = newPos.second;
    if (m_vecUnits[x][y].unit->isCorpse()) {
      attacker.unit->changeEnergy(m_vecUnits[x][y].unit,
                                  m_vecUnits[x][y].unit->getEnergy());
      clean(m_vecUnits[x][y]);
    } else {
      attacker.unit->changeEnergy(m_vecUnits[x][y].unit,
                                  m_vecUnits[x][y].unit->getEnergy() / 5);
      sun->changeEnergy(attacker.unit, BITE);
    }
  }
}

void
World::clean(unitInWorld& corpse)
{
  m_earthEnergy[corpse.pos.first][corpse.pos.second]->changeEnergy(
    corpse.unit, corpse.unit->getEnergy());
  corpse.unit->clean();
}

void
World::see(unitInWorld& unit, const directions direction)
{
  auto newPos = getNewPos(unit.pos, direction);
  if (unit.unit->isNo_Unit())
    unit.unit->setAnswer(answer::Empty);
  else
    unit.unit->setAnswer(answer::UnitIsHere);
}

void
World::wait(unitInWorld& waiter)
{
  sun->changeEnergy(waiter.unit, 1);
}

void
World::kill(unitInWorld& unit)
{
  long long energy = unit.unit->getEnergy();
  unit.unit->kill(energy + CORPSE_ENERGY);
}

void
World::till(unitInWorld& unit)
{
  tills++;
  unit.unit->changeEnergy(
    m_earthEnergy[unit.pos.first][unit.pos.second],
    m_earthEnergy[unit.pos.first][unit.pos.second]->getEnergy() / 100);
}

void
World::makeChild(unitInWorld& unit, const size_t count)
{
  childrenCount += count;
  bornCount++;
  for (size_t i = 0; i < count; i++) {
    auto newPos = findPlace(unit.pos);
    if (newPos == NULL_POS)
      return;
    long long energyPerChild = unit.unit->getEnergy() / (count + 1);
    m_vecUnits[newPos.first][newPos.second] =
      unitInWorld(unit.unit->Child(energyPerChild + rand() % 50 - 25), newPos);
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
  return (m_vecUnits[newPos.first][newPos.second].unit->isNo_Unit());
}

bool
World::canAttack(const std::pair<size_t, size_t>& newPos)
{
  if (newPos.first >= m_vecUnits.size() ||
      newPos.second >= m_vecUnits[0].size())
    return false;
  return !(m_vecUnits[newPos.first][newPos.second].unit->isNo_Unit());
}

void
World::photosynthesis(unitInWorld& unit)
{
  unit.unit->changeEnergy(sun, unit.pos.first / 10);
}

std::pair<size_t, size_t>
World::getNewPos(const std::pair<size_t, size_t>& pos,
                 const directions& direction)
{
  std::pair<size_t, size_t> newPos = pos;
  switch (direction) {
    case directions::LEFT:
      newPos.second--;
      break;
    case directions::RIGHT:
      newPos.second++;
      break;
    case directions::UP:
      newPos.first--;
      break;
    case directions::DOWN:
      newPos.first++;
      break;
    case directions::UP_LEFT:
      newPos.first--;
      newPos.second--;
      break;
    case directions::UP_RIGHT:
      newPos.first--;
      newPos.second++;
      break;
    case directions::DOWN_LEFT:
      newPos.first++;
      newPos.second--;
      break;
    case directions::DOWN_RIGHT:
      newPos.first++;
      newPos.second++;
      break;
  }
  newPos.first = (newPos.first + m_vecUnits.size()) % m_vecUnits.size();
  newPos.second = (newPos.first + m_vecUnits[0].size()) % m_vecUnits[0].size();
}

std::pair<size_t, size_t>
World::getNewPos(const std::pair<size_t, size_t>& pos,
                 const std::pair<int, int>& direction)
{
  std::pair<size_t, size_t> newPos;
  newPos.first =
    (pos.first + direction.first + m_vecUnits.size()) % m_vecUnits.size();
  newPos.second = (pos.second + direction.second + m_vecUnits[0].size()) %
                  m_vecUnits[0].size();
  return newPos;
}

std::pair<size_t, size_t>
World::findPlace(const std::pair<size_t, size_t>& pos)
{
  std::vector<std::pair<size_t, size_t>> possiblePlaces;
  possiblePlaces.reserve(8);
  for (int i = -1; i <= 1; i++)
    for (int j = -1; j <= 1; j++) {
      auto newPos = getNewPos(pos, std::make_pair(i, j));
      if (canGo(newPos))
        possiblePlaces.push_back(newPos);
    }
  if (possiblePlaces.empty())
    return NULL_POS;
  else
    return possiblePlaces[rand() % possiblePlaces.size()];
}

size_t
World::getNumberOfAlives()
{
  size_t result = 0;
  for (auto row : m_vecUnits)
    for (auto unit : row) {
      if (!unit.unit->isNo_Unit() && !unit.unit->isCorpse())
        result++;
    }
  return result;
}

void
World::show() const
{
  long long sumEnergy = 0;
  long long averageAge = 0;
  long long count = 0;
  for (auto row : m_vecUnits) {
    for (auto unit : row) {
      if (unit.unit->isNo_Unit())
        std::cout << " .";
      else if (unit.unit->isCorpse()) {
        std::cout << " x";
      } else {
        std::cout << " O";
        sumEnergy += unit.unit->getEnergy();
        averageAge += unit.unit->getAge();
        count++;
      }
    }
    std::cout << std::endl;
  }
  std::cout << "Summary energy for world: " << sumEnergy << std::endl;
  std::cout << "Average age: " << (averageAge + .0) / count << std::endl;
  std::cout << "Tills: " << tills << "\tAttacks: " << attacks << std::endl;
  std::cout << "Average children count: "
            << (childrenCount + .0) / (bornCount + 0.000001) << std::endl;
}
