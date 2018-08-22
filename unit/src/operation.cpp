#include "operation.hpp"

Operation::Operation(const operationType& _type)
  : type(_type)
{}

size_t
Operation::parseOperationType(const std::vector<char>& gen)
{
  size_t index = 0;
  for (auto bit : gen)
    index = (index * 2) + bit;
  return index;
}

bool
Operation::isWorldOperation()
{
  return operationType::PHOTOSYNTESIS == type || operationType::SEE == type ||
         operationType::GO == type || operationType::WAIT == type ||
         operationType::MAKE_CHILD == type || operationType::DIE == type ||
         operationType::TILL == type || operationType::ATTACK == type;
}

bool
operator==(const Operation& lhs, const Operation& rhs)
{
  return lhs.type == rhs.type && lhs.params == rhs.params;
}

bool
operator!=(const Operation& lhs, const Operation& rhs)
{
  return !(lhs == rhs);
}

std::vector<char>
intToChar(size_t value, const size_t length)
{
  std::vector<char> gen;
  gen.resize(length);
  for (int i = length - 1; i >= 0; i--) {
    gen[i] = value % 2;
    value /= 2;
  }
  return gen;
}
