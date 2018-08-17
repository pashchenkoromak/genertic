#include <string>
#include <vector>

namespace CommandLength {
const size_t GOTO = 6;
const size_t ANSWER = 1;
const size_t NUMBER = 4;
const size_t OPERATION = 4;
const size_t DIRECTION = 3;
const size_t BOOL = 4;
const size_t MATH = 3;
const size_t CONST_BOOL = 1;
} // namespace CommandLength

/// @brief list of possible answers by world
enum answer
{
  Empty,
  UnitIsHere
};

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

std::string
directionToString(const directions& rhs);

enum maths
{
  PLUS,
  MINUS,
  NUMBER_CONST,
  ENERGY,
  MULTIPLE,
  DIVIDE,
  REST_DEVIDE,
  ANSWER
};

enum boolMath
{
  BOOL_CONST,
  LESS,
  MORE,
  EQUAL,
  NO_EQUAL,
  NO,
  LESS_EQUAL,
  MORE_EQUAL,
  AND,
  OR,
  XOR
};

enum operationType
{
  GOTO, //
  IF,
  PHOTOSYNTESIS,
  SEE,
  GO,
  // WHILE,
  WAIT,
  MAKE_CHILD,
  DIE,
  /// NOTE: It must be the last one. Used as a way to count elements.
  TYPE_COUNT
};

struct Operation
{
  Operation() = default;
  ~Operation() = default;
  Operation(const operationType&);
  /// @brief Get operation type, which is coded into vector
  /// @param[in] gen - sequence of bits
  /// @return type of operation
  static operationType parseOperationType(const std::vector<char>& gen);
  bool isWorldOperation();
  operationType type;
  std::vector<std::string> params;
};
