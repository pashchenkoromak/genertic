#include "genom.hpp"
#include <string>
#include <vector>

#ifndef UNIT_HPP
#define UNIT_HPP

/// @class Unit
/// @brief includes genom and some additional info, that could be used be World.
class Unit
{
public:
  /// @brief construct unit with some energy.
  /// @param[in] energy - start energy.
  /// @note Every unit has unique id.
  Unit(const long long energy = START_ENERGY);

  /// @brief Copy unit.
  /// @param[in] rhs - base unit.
  /// @note Be care: you'll have 2 units with equals id
  Unit(const Unit& rhs);

  /// @brief Create new unit. He is the same as base unit, but has unique id and
  /// different energy
  /// @param[in] rhs - base unit.
  /// @param[in] energy - start energy for constructed unit.
  Unit(const Unit& rhs, const long long energy);

  /// @brief mutation of genom
  /// @result some changes in genom
  virtual void mutation();

  /// @brief get next move of unit
  /// @return Operation to the World
  virtual Operation nextMove();

  /// @brief changes energy for value
  /// @param[in] value - adding to the energy value
  /// @note value can be <0
  void changeEnergy(const long long value);

  /// @brief set answer by the world to the unit
  /// @param[in] rhs - answer be the world.
  void setAnswer(const answer& rhs);

  /// @brief operator =
  /// @param[in] rhs - base unit
  /// @result - the same unit with the same id.
  Unit& operator=(const Unit& rhs);

  /// @brief operators == and !=
  /// @note it checking equality only using id.
  /// @{
  friend bool operator==(const Unit& lhs, const Unit& rhs);
  friend bool operator!=(const Unit& lhs, const Unit& rhs);
  /// @}

  /// @brief Make unit with id = -1
  static Unit NO_UNIT();
  /// @brief Make unit with id = -2
  static Unit CORPSE();

  /// @brief Energy getter
  /// @return current energy of unit
  long long getEnergy() const;

  /// @brief Age getter
  /// @return current unit age
  long long getAge() const;

  /// @brief makes new unit. It`s the same as base unit, but with other energy
  /// and id.
  /// @param[in] rhs - base unit
  /// @param[in] - start energy
  Unit Child(const Unit& rhs, const long long energy);

private:
  /// @brief next free id
  static int nextId;

  /// @brief starting energy for every unit by default
  static const long long START_ENERGY = 400;

  /// @brief current unit id
  int id;

  /// @brief age of unit
  size_t m_age;

  /// @brief energy of unit
  long long m_energy;

  /// @brief genom
  Genom m_genom;

  /// @brief last answer by world
  answer m_worldAnswer;
};

#endif // UNIT_HPP
