#include "world.hpp"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>

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

bool World::canGo(std::pair<uint, uint>& newPos)
{
   return (*m_vecUnits[newPos.first][newPos.second].unit == Unit::NO_UNIT);
}

void World::photosintes(unitInWorld& unit)
{
   unit.unit->changeEnergy(unit.pos.first);
}

std::pair<uint, uint> World::getNewPos(const std::pair<uint, uint>& pos, const std::string& direction)
{
   std::pair<uint, uint> newPos = pos;
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
