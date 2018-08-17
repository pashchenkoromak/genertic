#include "unit.hpp"

Unit::Unit()
{
    static int nextId = 0;
    id = nextId++;
}

void Unit::mutation()
{
    m_genom.mutation();
}

Operation Unit::nextMove()
{
   return m_genom.nextMove(m_energy);
}

void Unit::changeEnergy(const long long value)
{
    m_energy += value;
}

void Unit::setAnswer(const answer &rhs)
{
    m_worldAnswer = rhs;
}

Unit &Unit::operator=(const Unit &rhs)
{
    m_energy = rhs.m_energy;
    m_genom = rhs.m_genom;
    m_worldAnswer = rhs.m_worldAnswer;
    id = rhs.id;
    return *this;
}

Unit Unit::NO_UNIT()
{
    static Unit NO_UNIT;
    NO_UNIT.id = -1;
    return NO_UNIT;
}

bool operator==(const class Unit& lhs, const class Unit& rhs)
{
   return lhs.id == rhs.id;
}
bool operator!=(const class Unit& lhs, const class Unit& rhs)
{
   return !(lhs.id == rhs.id);
}

