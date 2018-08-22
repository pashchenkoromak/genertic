#include "IUnit.hpp"
#include "genom.hpp"
#include <string>
#include <vector>

#ifndef UNIT_HPP
#define UNIT_HPP

/// @class Unit : public IUnit
/// @brief includes genom and some additional info, that could be used be World.
class Unit : public IUnit
{
public:
  /// @brief construct unit with some energy.
  /// @param[in] energy - start energy.
  /// @note Every unit has unique id.
  Unit(const long long energy = IUnit::START_ENERGY);

  /// @brief Copy unit.
  /// @param[in] rhs - base unit.
  /// @note Be care: you'll have 2 units with equals id
  Unit(const Unit& rhs);

  /// @brief Create new unit. He is the same as base unit, but has unique id and
  /// different energy
  /// @param[in] rhs - base unit.
  /// @param[in] energy - start energy for constructed unit.
  Unit(const Unit& rhs, const long long energy);

  /// @brief operator =
  /// @param[in] rhs - base unit
  /// @result - the same unit with the same id.
  Unit& operator=(const Unit& rhs);

  /// @brief mutation of genom
  /// @result some changes in genom
  virtual void mutation();

  /// @brief get next move of unit
  /// @return Operation to the World
  virtual Operation nextMove();

  /// @brief makes new unit. It`s the same as base unit, but with other energy
  /// and id.
  /// @param[in] energy - start energy
  /// @note: this must return a pointer to Unit! (non IUnit)
  virtual std::shared_ptr<IUnit> makeChild() override;

private:
  /// @brief genom
  Genom m_genom;
};

#endif // UNIT_HPP
