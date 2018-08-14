#include "unit.hpp"
#include <memory>
#include <vector>

struct unitInWorld
{
   std::shared_ptr<Unit> unit;
   std::pair<size_t, size_t> pos;
};

class World
{
public:
   World();
   ~World();
   void getNextMove();

private:
   std::vector<std::vector<unitInWorld>> m_vecUnits;
   std::vector<std::string> split(const std::string& data);
   void handleOperation(const Operation& operation, unitInWorld& unit);
   void photosintes(unitInWorld& unit);
   std::pair<size_t, size_t> getNewPos(const std::pair<size_t, size_t>& pos, const std::string& direction);
   void go(unitInWorld& unit, const std::string& direction);
   void see(unitInWorld& unit, const std::string& direction);
   void wait(unitInWorld& unit);
   void clear(unitInWorld& unit);
   void kill(unitInWorld& unit);
   bool canGo(const std::pair<size_t, size_t>& newPos);
};
