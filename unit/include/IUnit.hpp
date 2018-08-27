#include "operation.hpp"
#include <memory>
#ifndef IUNIT_HPP
#define IUNIT_HPP

/// @class IUnit
/// @brief Abstract class IUnit, which is used by World
class IUnit
{
public:
  /// @brief construct unit with some energy.
  /// @param[in] energy - start energy.
  /// @note Every alive unit has unique id.
  IUnit(const long long energy = START_ENERGY);
  /// @brief copyable
  /// @note: copy has unique id too
  IUnit(const IUnit&);
  /// @brief move constructable
  IUnit(IUnit&&);
  /// @brief move assignable
  IUnit& operator=(IUnit&&);

  /// @brief return an unique id of unit
  /// @return id as int
  int getId() const;

  /// @brief mutation of unit
  /// @result some changes in genom
  virtual void mutation();

  /// @brief RAII wrapper for nextMove.
  Operation nextOperation();
  /// @brief get next move of unit
  /// @return Operation to the World
  virtual Operation nextMove();

  /// @brief changes energy for value
  /// @param[in] energySource - try to get energy from this unit
  /// @param[in] value - adding to the energy value
  /// @note value can be <0
  void changeEnergy(std::shared_ptr<IUnit> energySource, const long long value);
  /// @brief If need any changes on change energy action
  virtual void onChangeEnergy();

  /// @brief set answer by the world to the unit
  /// @param[in] rhs - answer by the world.
  void setAnswer(const answer& rhs);
  /// @brief If need any changes on set answer action
  virtual void onSetAnswer();

  /// @brief set message to the unit
  /// @param[in] rhs - message.
  void setMessage(const size_t& rhs);
  /// @brief If need any changes on set message action
  virtual void onSetMessage();

  /// @brief Energy getter
  /// @return current energy of unit
  long long getEnergy() const;

  /// @brief Age getter
  /// @return current unit age
  long long getAge() const;

  /// @brief makes new unit. It`s the same as base unit, but with other energy
  /// and id.
  /// @param[in] energy - start energy
  std::shared_ptr<IUnit> Child(const long long energy);
  virtual std::shared_ptr<IUnit> makeChild();
  /// @brief operators == and !=
  /// @note it checking equality only using id.
  /// @{
  friend bool operator==(const IUnit& lhs, const IUnit& rhs);
  friend bool operator!=(const IUnit& lhs, const IUnit& rhs);
  /// @}

  /// @brief NO_UNIT
  static std::shared_ptr<IUnit> NO_UNIT();
  static std::shared_ptr<IUnit> CORPSE();
  bool isNo_Unit() const;
  bool isCorpse() const;
  /// @brief transform unit to Corpse
  void kill(const long long energy);
  /// @brief transform unit to No_Unit
  void clean();

protected:
  /// @brief starting energy for every unit by default
  static const long long START_ENERGY = 400;

  /// @brief getter for answer
  answer getAnswer() const;

  /// @brief getter for message
  size_t getMessage() const;

private:
  /// @brief Add energy
  void addEnergy(const long long energy);

  static const int NO_UNIT_ID = -1;
  static const int CORPSE_ID = -2;
  /// @brief next free id
  static int nextId;

  /// @brief current unit id
  int id;

  /// @brief age of unit
  size_t m_age;

  /// @brief energy of unit
  long long m_energy;

  /// @brief last answer by world
  answer m_worldAnswer;

  size_t m_message;
};

#endif // IUNIT_HPP
