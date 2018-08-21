#include "unit.hpp"

Unit::Unit(const long long energy)
  : m_energy(energy)
  , m_age(0)
{
  id = Unit::nextId++;
}

Unit::Unit(const Unit& rhs)
  : m_age(rhs.m_age)
  , id(rhs.id)
  , m_energy(rhs.m_energy)
  , m_genom(rhs.m_genom)
{}

Unit
Unit::Child(const Unit& rhs, const long long energy)
{
  Unit child = rhs;
  child.m_age = 0;
  child.m_energy = energy;
  child.id = Unit::nextId++;
  return child;
}

void
Unit::mutation()
{
  m_genom.mutation();
}

Operation
Unit::nextMove()
{
  m_age++;
  return m_genom.nextMove(m_energy);
}

void
Unit::changeEnergy(const long long value)
{
  m_energy += value;
}

void
Unit::setAnswer(const answer& rhs)
{
  m_worldAnswer = rhs;
}

Unit&
Unit::operator=(const Unit& rhs)
{
  m_energy = rhs.m_energy;
  m_genom = rhs.m_genom;
  m_age = 0;
  m_worldAnswer = rhs.m_worldAnswer;
  id = rhs.id;
  return *this;
}

Unit
Unit::NO_UNIT()
{
  static Unit NO_UNIT;
  NO_UNIT.id = -1;
  return NO_UNIT;
}

Unit
Unit::CORPSE()
{
  static Unit CORPSE;
  CORPSE.id = -2;
  return CORPSE;
}

long long
Unit::getEnergy() const
{
  return m_energy;
}

long long
Unit::getAge() const
{
  return m_age;
}

bool
operator==(const class Unit& lhs, const class Unit& rhs)
{
  return lhs.id == rhs.id;
}
bool
operator!=(const class Unit& lhs, const class Unit& rhs)
{
  return !(lhs.id == rhs.id);
}

int Unit::nextId = 0;
