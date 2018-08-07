#include <string>
#include <vector>

class Unit
{
public:
   Unit();
   std::string nextMove();
   void changeEnergy(const long long value);
   friend bool operator==(const Unit& lhs, const Unit& rhs);
   friend bool operator!=(const Unit& lhs, const Unit& rhs);
   static const Unit NO_UNIT;

private:
   int id;
   long long m_energy;
   Unit(const int id);
};
