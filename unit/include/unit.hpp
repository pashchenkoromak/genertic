#include "genom.hpp"
#include <string>
#include <vector>

class Unit {
public:
   Unit();
   Operation nextMove();
   void changeEnergy(const long long value);
   Unit& operator=(const Unit& rhs);
   friend bool operator==(const Unit& lhs, const Unit& rhs);
   friend bool operator!=(const Unit& lhs, const Unit& rhs);
   static const Unit NO_UNIT;

private:
   int id;
   long long m_energy;
   Genom m_genom;
   Unit(const int id);
   answer m_worldAnswer;
};
