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
                row.push_back(std::make_shared<unitInWorld>(std::make_shared(Unit), std::make_pair(i, j)));
            else row.push_back(std::make_shared<unitInWorld>(std::make_shared(Unit::NO_UNIT), std::make_pair(i, j)));
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

void World::wait(unitInWorld &unit)
{}

void World::kill(unitInWorld &unit)
{
    m_vecUnits[unit.pos.first][unit.pos.second] = Unit::NO_UNIT;
}

bool World::canGo(const std::pair<size_t, size_t>& newPos)
{
   return (*m_vecUnits[newPos.first][newPos.second].unit == Unit::NO_UNIT);
}

void World::photosintes(unitInWorld& unit)
{
   unit.unit->changeEnergy(unit.pos.first);
}

std::pair<size_t, size_t> World::getNewPos(const std::pair<size_t, size_t>& pos, const std::string& direction)
{
   std::pair<size_t, size_t> newPos = pos;
   if (direction == "left")
      newPos.second--;
   if (direction == "right")
      newPos.second++;
   if (direction == "up")
      newPos.first--;
   if (direction == "down")
      newPos.first++;
   if (direction == "upleft")
   {
      newPos.first--;
      newPos.second--;
   }
   if (direction == "upright")
   {
      newPos.first--;
      newPos.second++;
   }
   if (direction == "downleft")
   {
      newPos.first++;
      newPos.second--;
   }
   if (direction == "downright")
   {
      newPos.first++;
      newPos.second++;
   }
   newPos.first = (newPos.first + m_vecUnits.size()) % m_vecUnits.size();
   newPos.second = (newPos.first + m_vecUnits[0].size()) % m_vecUnits[0].size();
}
