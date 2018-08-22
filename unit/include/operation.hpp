#include <string>
#include <vector>

#ifndef OPERATION_HPP
#define OPERATION_HPP

/// @namespace CommandLength
/// @brief CommandLength is a namespace with length of different commmands
namespace CommandLength {

/// @brief After every GOTO command there are number of the next command
const size_t GOTO = 6;

/// @brief Length of server's answer
const size_t ANSWER = 1;

/// @brief number const
const size_t NUMBER = 4;

/// @brief Operation
/// @note Be care, when add new operations. If there is not enough, some new can
/// be ignored!
const size_t OPERATION = 4;

/// @brief Direction
const size_t DIRECTION = 3;

/// @brief Bool command (<, >, ==, &&, etc).
const size_t BOOL = 4;

/// @brief Math ariphmetic command (+, -, *, /, %, etc).
const size_t MATH = 3;

/// @brief true or false
const size_t CONST_BOOL = 1;

/// @brief count of children: 0..8
const size_t CHILD_COUNT = 3;
} // namespace CommandLength

/// @enum answer
/// @brief list of possible answers by world
enum answer
{
  /// @brief Nothing
  Empty,
  /// @brief Some unit
  UnitIsHere
  // TODO: add corpse
};

/// @enum directions
/// @brief includes 8 directions
/// @note No need to explane their meaning
enum directions
{
  LEFT,
  RIGHT,
  UP,
  DOWN,
  UP_LEFT,
  DOWN_LEFT,
  UP_RIGHT,
  DOWN_RIGHT
};

/// @brief converts int value to a char vector of bits with given length
/// @param[in] value - integer value > 0
/// @param[in] length - length of result vector
/// @return integer as a char vector of bits.
std::vector<char>
intToChar(size_t value, const size_t length);

/// @enum maths
/// @brief math commands
/// @note In math expressions used prefix notation: + 3 4, for example.
enum maths
{
  /// @brief +
  PLUS,
  /// @brief -
  MINUS,
  /// @brief some const
  NUMBER_CONST,
  /// @brief getting energy of unit
  ENERGY,
  /// @brief *
  MULTIPLE,
  /// @brief /
  DIVIDE,
  /// @brief %
  REST_DEVIDE,
  /// @brief answer by World
  ANSWER
};

/// @enum boolMath
/// @brief bool commands
enum boolMath
{
  /// @brief boolean constant
  BOOL_CONST,
  /// @brief <
  LESS,
  /// @brief >
  MORE,
  /// @brief ==
  EQUAL,
  /// @brief !=
  NO_EQUAL,
  /// @brief !
  NO,
  /// @brief <=
  LESS_EQUAL,
  /// @brief >=
  MORE_EQUAL,
  /// @brief &&
  AND,
  /// @brief ||
  OR,
  /// @brief ^
  XOR
};

/// @enum operationType
/// @brief enum of possible main operations
enum operationType
{
  /// @brief GOTO uses number after itself, set next command position to this
  /// number
  GOTO,

  /// @brief IF checks some bool expression. And if it is true - goto
  /// first goto number, else - to the second Example (c++ code, ofc): A:
  /// photosyntesis if (Energy < 20)
  ///     goto A;
  /// else
  ///     goto B;
  /// B: make_child
  ///
  IF,

  /// @brief is a command to getting energy by the sun
  PHOTOSYNTESIS,

  /// @brief see if there is a unit in some direction
  /// (it looks in genom as SEE DIRECTION)
  SEE,
  /// @brief go in some direction (it looks in genom as GO DIRECTION)
  GO,
  /// @brief attacks in some direction (it looks in genom as ATTACK DIRECTION)
  ATTACK,
  /// @brief Do nothing
  WAIT,
  /// @brief Command to create a child to the world.
  /// @note it needs count of children as a parameter (number: 1..8)
  MAKE_CHILD,
  /// @brief try to get energy from the earth under unit
  TILL,

  /// @note: It must be the last one. Used as a way to count elements.
  TYPE_COUNT,
  /// @brief I'm not sure it must be here, but it's possible.
  DIE
};

/// @struct Operation
/// @brief operation has a type and (maybe) some parameters, like direction.
struct Operation
{
  /// @brief default constructor and destructor
  /// @{
  Operation() = default;
  ~Operation() = default;
  /// @}

  /// @brief creates operation of given type
  /// @param[in] type - type of new Operation
  Operation(const operationType& type);

  /// @brief Get operation type, which is coded into vector
  /// @param[in] gen - sequence of bits
  /// @return type of operation
  static size_t parseOperationType(const std::vector<char>& gen);
  /// @brief Check, if it's a command to the world or no.
  bool isWorldOperation();
  /// @brief operators == and !=
  /// @{
  friend bool operator==(const Operation& lhs, const Operation& rhs);
  friend bool operator!=(const Operation& lhs, const Operation& rhs);
  /// @}

  /// @brief type of Operation
  operationType type;

  /// @brief vector of parameters
  std::vector<size_t> params;
};

#endif // OPERATION_HPP
