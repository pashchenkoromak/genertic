#include "unit.hpp"

Unit::Unit(const long long energy)
  : IUnit(energy)
{}

Unit::Unit(const Unit& rhs)
  : m_genom(rhs.m_genom)
{}

void
Unit::mutation()
{
  m_genom.mutation();
}

Operation
Unit::nextMove()
{
  return m_genom.nextMove(getEnergy());
}

std::shared_ptr<IUnit>
Unit::makeChild()
{
  std::shared_ptr<Unit> child = std::make_shared<Unit>(*this);
  child->m_genom = m_genom;
  return child;
}
