#include "unit.hpp"

Unit::Unit()
{
    static int nextId = 0;
    id = nextId++;
}

Operation Unit::nextMove()
{
   return m_genom.nextMove(m_energy);
}

void Unit::changeEnergy(const long long value)
{
    m_energy += value;
}

Unit &Unit::operator=(const Unit &rhs)
{
    m_energy = rhs.m_energy;
    m_genom = rhs.m_genom;
    m_worldAnswer = rhs.m_worldAnswer;
    id = rhs.id;
    return *this;
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
