#include "common.hpp"

void
appendIntToChar(size_t value, std::vector<char>& vec, const size_t length)
{
  auto append = intToChar(value, length);
  vec.insert(vec.end(), append.begin(), append.end());
}

void
appender(std::vector<char>& vec)
{}
