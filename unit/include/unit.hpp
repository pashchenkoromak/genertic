#include "genom.hpp"
#include <string>
#include <vector>

#ifndef UNIT_HPP
#define UNIT_HPP

class Unit
{
public:
  Unit(const long long energy = START_ENERGY);
  Unit(const Unit& rhs);
  Unit(const Unit& rhs, const long long energy);
  void mutation();
  Operation nextMove();
  void changeEnergy(const long long value);
  void setAnswer(const answer& rhs);
  Unit& operator=(const Unit& rhs);
  friend bool operator==(const Unit& lhs, const Unit& rhs);
  friend bool operator!=(const Unit& lhs, const Unit& rhs);
  static Unit NO_UNIT();
  static Unit CORPSE();
  long long getEnergy() const;
  long long getAge() const;
  Unit Child(const Unit& rhs, const long long energy);

private:
  static int nextId;
  static const long long START_ENERGY = 400;
  int id;
  size_t m_age;
  long long m_energy;
  Genom m_genom;
  answer m_worldAnswer;
};

#endif // UNIT_HPP
