#include "unit.hpp"
#include <memory>
#include <vector>

struct unitInWorld
{
  unitInWorld() = default;
  unitInWorld(std::shared_ptr<Unit> _unit,
              const std::pair<size_t, size_t>& _pos)
    : unit(_unit)
    , pos(_pos)
  {}
  std::shared_ptr<Unit> unit;
  std::pair<size_t, size_t> pos;
};

class World
{
public:
  World();
  ~World() = default;
  void getNextMove();
  size_t getNumberOfAlives();
  void show() const;

private:
  const size_t BITE = 40;
  const double MUTATION_PROBABILITY = 0.5;
  const std::pair<size_t, size_t> NULL_POS = std::make_pair(SIZE_MAX, SIZE_MAX);
  std::vector<std::vector<unitInWorld>> m_vecUnits;
  std::vector<std::string> split(const std::string& data);
  void handleOperation(const Operation& operation, unitInWorld& unit);
  void photosintes(unitInWorld& unit);
  std::pair<size_t, size_t> getNewPos(const std::pair<size_t, size_t>& pos,
                                      const std::string& direction);
  std::pair<size_t, size_t> findPlace(const std::pair<size_t, size_t>& pos);
  void go(unitInWorld& unit, const std::string& direction);
  void attack(unitInWorld& unit, const std::string& direction);
  void see(unitInWorld& unit, const std::string& direction);
  void wait(unitInWorld& unit);
  void clear(unitInWorld& unit);
  void kill(unitInWorld& unit);
  void makeChild(unitInWorld& unit);
  bool canGo(const std::pair<size_t, size_t>& newPos);
  bool canAttack(const std::pair<size_t, size_t>& newPos);
};
