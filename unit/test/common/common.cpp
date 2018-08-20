#include "common.hpp"

void
appendIntToChar(size_t value, std::vector<char>& vec, const size_t length)
{
  auto append = intToChar(value, length);
  vec.insert(vec.end(), append.begin(), append.end());
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

void
appender(std::vector<char>& vec)
{}
