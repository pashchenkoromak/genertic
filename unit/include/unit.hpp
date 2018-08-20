#include "genom.hpp"
#include <string>
#include <vector>

#ifndef UNIT_HPP
#define UNIT_HPP

class Unit
{
public:
  Unit();
  void mutation();
  Operation nextMove();
  void changeEnergy(const long long value);
  void setAnswer(const answer& rhs);
  Unit& operator=(const Unit& rhs);
  friend bool operator==(const Unit& lhs, const Unit& rhs);
  friend bool operator!=(const Unit& lhs, const Unit& rhs);
  static Unit NO_UNIT();

private:
  int id;
  long long m_energy;
  Genom m_genom;
  answer m_worldAnswer;
};

#endif // UNIT_HPP
