#include "actor.hpp"

Actor::Actor(const long long energy) : m_energy(energy), m_age(0) { id = Actor::nextId++; }

Actor::Actor(Actor&& rhs)
    : m_age(std::move(rhs.m_age)),
      m_energy(std::move(rhs.m_energy)),
      m_genom(std::move(rhs.m_genom)),
      m_worldAnswer(std::move(rhs.m_worldAnswer))
{
    rhs.m_energy = 0;
    rhs.m_age = 0;
}

Actor Actor::Child(const Actor& rhs, const long long energy)
{
    Actor child = rhs;
    child.m_age = 0;
    child.m_energy = energy;
    child.id = Actor::nextId++;
    return child;
}

void Actor::mutation() { m_genom.mutation(); }

Operation Actor::nextMove()
{
    m_age++;
    return m_genom.nextMove(m_energy);
}

void Actor::changeEnergy(const long long value) { m_energy += value; }

void Actor::setAnswer(const answer& rhs) { m_worldAnswer = rhs; }

Actor Actor::NO_UNIT()
{
    static Actor NO_UNIT;
    NO_UNIT.id = -1;
    return NO_UNIT;
}

Actor Actor::CORPSE()
{
    static Actor CORPSE;
    CORPSE.id = -2;
    return CORPSE;
}

long long Actor::getEnergy() const { return m_energy; }

long long Actor::getAge() const { return m_age; }

bool operator==(const class Actor& lhs, const class Actor& rhs) { return lhs.id == rhs.id; }
bool operator!=(const class Actor& lhs, const class Actor& rhs) { return !(lhs.id == rhs.id); }

int Actor::nextId = 0;
