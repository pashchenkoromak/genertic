#include "unit.hpp"

void Unit::changeEnergy(const long long value)
{
   m_energy += value;
}

bool operator==(const Unit& lhs, const Unit& rhs)
{
   return lhs.id == rhs.id;
}
bool operator!=(const Unit& lhs, const Unit& rhs)
{
   return !(lhs.id == rhs.id);
}

const Unit Unit::NO_UNIT = Unit(-1);
