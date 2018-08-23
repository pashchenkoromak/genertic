#include "IUnit.hpp"
#include "unit.hpp"
#include <memory>
#include <vector>

/// @struct unitInWorld
/// @brief includes unit and his position
struct unitInWorld
{
  /// @brief default constructor
  unitInWorld() = default;

  /// @brief constructor with data
  unitInWorld(std::shared_ptr<IUnit> _unit,
              const std::pair<size_t, size_t>& _pos)
    : unit(_unit)
    , pos(_pos)
  {}

  /// @brief unit
  std::shared_ptr<IUnit> unit;

  /// @brief position
  std::pair<size_t, size_t> pos;
};

/// @class World
/// @brief it includes units and can wrap their moves.
class World
{
public:
  /// @brief Constructor. It creates a world, and fill it due to FULLNESS with
  /// units.
  /// @note It also fill earthEnergy.
  World();

  /// @brief Default destructor
  ~World() = default;

  /// @brief Get next state of the world.
  void getNextMove();

  /// @brief Get number of Alives unit in the world
  size_t getNumberOfAlives();

  /// @brief show the world to the std::cout
  void show() const;

private:
  std::shared_ptr<IUnit> sun;

  /// @brief some statistic info about unit moves
  /// @{
  size_t attacks = 0;
  size_t tills = 0;
  size_t childrenCount;
  size_t bornCount;
  /// @}

  /// @brief Energy, that you can take when bite anyone.
  const size_t BITE = 10;

  /// @brief Each iteration, every unit must pay a penalty to sun:
  /// unit age * AGE_PENALTY.
  const double AGE_PENALTY = 0.2;

  /// @brief Probability for children to mutate
  const double MUTATION_PROBABILITY = 0.5;

  /// @brief Fullness of world in the start.
  const double FULLNESS = 0.3333;

  /// @brief Default energy of any corpse.
  const long long CORPSE_ENERGY = 10;

  /// @brief Some position, that means "HERE IS NO POSITION!".
  const std::pair<size_t, size_t> NULL_POS = std::make_pair(SIZE_MAX, SIZE_MAX);

  /// @brief Earth energy matrix. Used for tilling.
  std::vector<std::vector<std::shared_ptr<IUnit>>> m_earthEnergy;

  /// @brief Units matrix
  std::vector<std::vector<unitInWorld>> m_vecUnits;

  /// @brief Handles operation by unit
  void handleOperation(const Operation& operation, unitInWorld& unit);

  /// @brief Get new position, which is pos + direction.
  /// @param[in] pos - current position.
  /// @param[in] direction - shift direction as string (LEFT, RIGHT, etc).
  /// @return New position.
  std::pair<size_t, size_t> getNewPos(const std::pair<size_t, size_t>& pos,
                                      const directions& direction);
  /// @brief Get new position, which is pos + direction
  /// @param[in] pos - current position
  /// @param[in] direction - shift direction as pair<int, int>
  /// @return New position
  std::pair<size_t, size_t> getNewPos(const std::pair<size_t, size_t>& pos,
                                      const std::pair<int, int>& direction);
  /// @brief Add energy to the unit, due to his position
  /// @param[in] unit - doer
  void photosynthesis(unitInWorld& unit);

  /// @brief finds an empty place near the unit
  std::pair<size_t, size_t> findPlace(const std::pair<size_t, size_t>& pos);

  /// @brief move unit to the direction
  /// @param[in] unit - doer
  /// @param[in] direction - where to move
  void go(unitInWorld& unit, const directions direction);

  /// @brief attack in direction
  /// @param[in] unit - doer
  /// @param[in] direction - where to attack
  /// @note if there is nothing - nothing will happened
  void attack(unitInWorld& unit, const directions direction);

  /// @brief clean a corpse to the earth.
  /// @param[in] unit - unit to clean
  void clean(unitInWorld& unit);

  /// @brief see to the direction
  /// @param[in] unit - doer
  /// @param[in] direction - where to move
  /// @result unit will have an answer by the world
  void see(unitInWorld& unit, const directions direction);

  /// @brief unit doesnt want to do anything
  /// @param[in] unit - some lazy unit
  void wait(unitInWorld& unit);

  /// @brief create a corpse from a unit
  /// @param[in] unit - unit, who will die
  void kill(unitInWorld& unit);

  /// @brief till ground under the unit to get energy.
  /// @param[in] unit - tiller
  void till(unitInWorld& unit);

  /// @brief creates children where it's possible around the unit
  /// @param[in] unit - parent
  void makeChild(unitInWorld& unit, const size_t count);

  /// @brief check, if there is no units, and it's possible to go there
  /// @param[in] newPos - position for check
  bool canGo(const std::pair<size_t, size_t>& newPos);

  /// @brief check, if there is a unit or a corpse to attack
  /// @param[in] newPos - position for check
  bool canAttack(const std::pair<size_t, size_t>& newPos);
};
