#include "operation.hpp"

Operation::Operation(const operationType& _type)
  : type(_type)
{}

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
  return std::move(gen);
}
