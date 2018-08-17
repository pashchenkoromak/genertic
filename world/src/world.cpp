#include "world.hpp"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>

World::World()
{
    int n = 100;
    int m = 100;
    m_vecUnits.resize(n);
    for(int i = 0; i < n; i++)
    {
        m_vecUnits[i].reserve(m);
        for(int j = 0; j < m; j++)
        {
            if (rand() % 3 == 0)
                m_vecUnits[i][j] = unitInWorld(std::make_shared<Unit>(), std::make_pair(i, j));
            else m_vecUnits[i][j] = unitInWorld(std::make_shared<Unit>(Unit::NO_UNIT()), std::make_pair(i, j));
        }
    }
}

void World::getNextMove()
{
   for (auto line : m_vecUnits)
      for (auto unit : line)
         handleOperation(unit.unit->nextMove(), unit);
}


void World::handleOperation(const Operation& operation, unitInWorld& unit)
{
   switch (operation.type)
   {
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
      default:
         photosintes(unit);
   }
}
void World::go(unitInWorld& unit, const std::string& direction)
{
   auto newPos = getNewPos(unit.pos, direction);
   if (canGo(newPos))
   {
      std::swap(m_vecUnits[newPos.first][newPos.second], m_vecUnits[unit.pos.first][unit.pos.second]);
      unit.pos = newPos;
   }
}

void World::see(unitInWorld &unit, const std::string &direction)
{
    auto newPos = getNewPos(unit.pos, direction);
    if (*(unit.unit) == Unit::NO_UNIT())
        unit.unit->setAnswer(answer::Empty);
    else unit.unit->setAnswer(answer::UnitIsHere);
}

void World::wait(unitInWorld &unit)
{}

void World::kill(unitInWorld &unit)
{
    *unit.unit = Unit::NO_UNIT();
}

void World::makeChild(unitInWorld &unit)
{
    auto newPos = findPlace(unit.pos);
    if (newPos == NULL_POS)
        return;
    unit.unit->changeEnergy(-ENERGY_FOR_CHILD);
    m_vecUnits[newPos.first][newPos.second] = unitInWorld(std::make_shared<Unit>(*unit.unit), newPos);
    if (rand() % 10000 < MUTATION_PROBABILITY * 10000)
        m_vecUnits[newPos.first][newPos.second].unit->mutation();
}

bool World::canGo(const std::pair<size_t, size_t>& newPos)
{
   return (*m_vecUnits[newPos.first][newPos.second].unit == Unit::NO_UNIT());
}

void World::photosintes(unitInWorld& unit)
{
   unit.unit->changeEnergy(unit.pos.first);
}

std::pair<size_t, size_t> World::getNewPos(const std::pair<size_t, size_t>& pos, const std::string& direction)
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
   if (direction == directionToString(directions::UP_LEFT))
   {
      newPos.first--;
      newPos.second--;
   }
   if (direction == directionToString(directions::UP_RIGHT))
   {
      newPos.first--;
      newPos.second++;
   }
   if (direction == directionToString(directions::DOWN_LEFT))
   {
      newPos.first++;
      newPos.second--;
   }
   if (direction == directionToString(directions::DOWN_RIGHT))
   {
      newPos.first++;
      newPos.second++;
   }
   newPos.first = (newPos.first + m_vecUnits.size()) % m_vecUnits.size();
   newPos.second = (newPos.first + m_vecUnits[0].size()) % m_vecUnits[0].size();
}

std::pair<size_t, size_t> World::findPlace(const std::pair<size_t, size_t> &pos)
{
    for(int i = -1; i <= 1; i++)
        for(int j = -1; j <= 1; j++)
            if (canGo(std::make_pair(pos.first + i, pos.second + j)))
                return std::make_pair(pos.first + i, pos.second + j);
    return NULL_POS;
}
