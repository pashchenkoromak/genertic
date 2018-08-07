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


void World::handleOperation(const std::string& operation, unitInWorld& unit)
{
   // split operation with ' ' to vector of strings
   std::istringstream iss(operation);
   std::vector<std::string> operators{std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{}};

   if (operators[0] == "photosintes")
      photosintes(unit);
   else if (operators[0] == "go")
      go(unit, operators[1]);
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
