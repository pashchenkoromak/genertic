#include "IUnit.hpp"
#include <chrono>
#include <iostream>

IUnit::IUnit(const long long energy)
  : m_energy(energy)
  , m_age(0)
{
  id = IUnit::nextId++;
}

IUnit::IUnit(const IUnit& rhs)
  : m_energy(rhs.m_energy)
  , m_age(rhs.m_age)
  , m_worldAnswer(rhs.m_worldAnswer)
{
  id = IUnit::nextId++;
}

IUnit::IUnit(IUnit&& rhs)
  : m_energy(rhs.m_energy)
  , m_age(rhs.m_age)
  , id(rhs.id)
{
  rhs.m_energy = 0;
  rhs.m_age = 0;
  rhs.id = -1;
}

IUnit&
IUnit::operator=(IUnit&& rhs)
{
  id = rhs.id;
  m_energy = rhs.m_energy;
  m_age = rhs.m_age;
  rhs.id = NO_UNIT_ID;
  rhs.m_energy = 0;
  rhs.m_age = 0;
  return *this;
}

int
IUnit::getId() const
{
  return id;
}

void
IUnit::mutation()
{}

Operation
IUnit::nextOperation()
{
  m_age++;
  auto start = std::chrono::system_clock::now();
  Operation op = this->nextMove();
  auto end = std::chrono::system_clock::now();
  auto elapsed = end - start;
  addEnergy(-elapsed.count() / 50);
  if (m_energy <= 0)
    op.type = operationType::DIE;
  return op;
}

Operation
IUnit::nextMove()
{
  return Operation();
}

void
IUnit::changeEnergy(std::shared_ptr<IUnit> energySource, const long long value)
{
  long long gottenValue = std::min(value, energySource->getEnergy());
  energySource->addEnergy(-gottenValue);
  addEnergy(gottenValue);
  onChangeEnergy();
}

void
IUnit::onChangeEnergy()
{}

void
IUnit::setAnswer(const answer& rhs)
{
  m_worldAnswer = rhs;
  onSetAnswer();
}

void
IUnit::onSetAnswer()
{}

long long
IUnit::getEnergy() const
{
  return m_energy;
}

long long
IUnit::getAge() const
{
  return m_age;
}

std::shared_ptr<IUnit>
IUnit::Child(const long long energy)
{
  std::shared_ptr<IUnit> child = this->makeChild();
  child->m_age = 0;
  child->addEnergy(std::min(energy, m_energy));
  addEnergy(std::min(energy, m_energy));
  child->id = IUnit::nextId++;
  return child;
}

std::shared_ptr<IUnit>
IUnit::makeChild()
{
  std::cout << "Make IUnit child!" << std::endl;
}

std::shared_ptr<IUnit>
IUnit::NO_UNIT()
{

  static std::shared_ptr<IUnit> NO_UNIT = std::make_shared<IUnit>();
  NO_UNIT->id = -1;
  return NO_UNIT;
}

std::shared_ptr<IUnit>
IUnit::CORPSE()
{
  static std::shared_ptr<IUnit> CORPSE = std::make_shared<IUnit>();
  CORPSE->id = -2;
  return CORPSE;
}

bool
IUnit::isNo_Unit() const
{
  return NO_UNIT_ID == id;
}

bool
IUnit::isCorpse() const
{
  return CORPSE_ID == id;
}

void
IUnit::kill(const long long energy)
{
  m_energy = energy;
  id = CORPSE_ID;
}

void
IUnit::clean()
{
  id = NO_UNIT_ID;
}

void
IUnit::addEnergy(const long long energy)
{
  m_energy += energy;
}

bool
operator==(const class IUnit& lhs, const class IUnit& rhs)
{
  return lhs.id == rhs.id;
}
bool
operator!=(const class IUnit& lhs, const class IUnit& rhs)
{
  return !(lhs.id == rhs.id);
}

int IUnit::nextId = 0;
