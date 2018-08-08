#include "unit.hpp"

Operation Unit::nextMove()
{
   return m_genom.nextMove();
}

void Unit::changeEnergy(const long long value)
{
   m_energy += value;
}

bool operator==(const class Unit& lhs, const class Unit& rhs)
{
   return lhs.id == rhs.id;
}
bool operator!=(const class Unit& lhs, const class Unit& rhs)
{
   return !(lhs.id == rhs.id);
}

const class Unit Unit::NO_UNIT = Unit(-1);
