#include "unit.hpp"

#ifndef COMMON_HPP
#define COMMON_HPP

class testGenom : public Genom
{
public:
  testGenom() = default;
  virtual ~testGenom() = default;
  void setGenom(const std::vector<char>& rhs) { m_genom = rhs; }

  long long testParseIf(long long& energy) { parseIf(energy); }

  int testParseExpression(const size_t startCommand,
                          long long& energy,
                          size_t& next)
  {
    parseExpression(startCommand, energy, next);
  }
  bool testParseBoolExpression(const size_t startCommand,
                               long long& energy,
                               size_t& next)
  {
    parseBoolExpression(startCommand, energy, next);
  }
};

const long long START_ENERGY = 100;

std::vector<char>
intToChar(size_t value, const size_t length);
void
appendIntToChar(size_t value, std::vector<char>& vec, const size_t length);
/// ParseExpression block

void
appender(std::vector<char>& vec);
template<typename T_COMMAND, typename T_LENGTH, typename... T>
void
appender(std::vector<char>& vec, T_COMMAND command, T_LENGTH length, T... args)
{
  appendIntToChar(command, vec, length);
  appender(vec, args...);
}

#endif // COMMON_HPP
