#include "genom.hpp"
#include <string>
#include <vector>

#ifndef UNIT_HPP
#define UNIT_HPP

class Unit
{
public:
  Unit(const long long energy = 100);
  void mutation();
  Operation nextMove();
  void changeEnergy(const long long value);
  void setAnswer(const answer& rhs);
  Unit& operator=(const Unit& rhs);
  friend bool operator==(const Unit& lhs, const Unit& rhs);
  friend bool operator!=(const Unit& lhs, const Unit& rhs);
  static Unit NO_UNIT();
  long long getEnergy() const;
  long long getAge() const;

private:
  int id;
  size_t m_age;
  long long m_energy;
  Genom m_genom;
  answer m_worldAnswer;
};

#endif // UNIT_HPP
