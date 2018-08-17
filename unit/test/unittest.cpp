#include "unit.hpp"
#include "gtest/gtest.h"
#include <iostream>

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
appendIntToChar(size_t value, std::vector<char>& vec, const size_t length)
{
  auto append = intToChar(value, length);
  vec.insert(vec.end(), append.begin(), append.end());
}
/// ParseExpression block

void
appender(std::vector<char>& vec)
{}
template<typename T_COMMAND, typename T_LENGTH, typename... T>
void
appender(std::vector<char>& vec, T_COMMAND command, T_LENGTH length, T... args)
{
  appendIntToChar(command, vec, length);
  appender(vec, args...);
}

void
test(const std::vector<char>& gen,
     const size_t resultPos,
     const long long finalEnergy,
     const long long correctResult)
{
  testGenom tgen;

  size_t next = 0;
  long long energy = START_ENERGY;
  tgen.setGenom(gen);
  int result = tgen.testParseExpression(next, energy, next);
  ASSERT_EQ(next, resultPos);
  ASSERT_EQ(result, correctResult);
  ASSERT_EQ(energy, finalEnergy);
}

// test plus parser
TEST(ParseExpression, Const)
{
  std::vector<char> gen;
  appender(
    gen, maths::NUMBER_CONST, CommandLength::MATH, 1, CommandLength::NUMBER);
  test(gen, CommandLength::MATH + CommandLength::NUMBER, START_ENERGY - 1, 1);
}

// test plus parser
TEST(ParseExpression, Plus)
{
  std::vector<char> gen;
  appender(gen,
           maths::PLUS,
           CommandLength::MATH,
           maths::NUMBER_CONST,
           CommandLength::MATH,
           1,
           CommandLength::NUMBER,
           maths::NUMBER_CONST,
           CommandLength::MATH,
           1,
           CommandLength::NUMBER);
  size_t finalPos = CommandLength::MATH * 3 + CommandLength::NUMBER * 2;
  test(gen, finalPos, START_ENERGY - 3, 2);
}

// test plus parser
TEST(ParseExpression, Minus)
{
  std::vector<char> gen;
  appender(gen,
           maths::MINUS,
           CommandLength::MATH,
           maths::NUMBER_CONST,
           CommandLength::MATH,
           1,
           CommandLength::NUMBER,
           maths::NUMBER_CONST,
           CommandLength::MATH,
           1,
           CommandLength::NUMBER);
  size_t finalPos = CommandLength::MATH * 3 + CommandLength::NUMBER * 2;
  test(gen, finalPos, START_ENERGY - 3, 0);
}

// test multiple parser
TEST(ParseExpression, Multiple)
{
  std::vector<char> gen;

  appender(gen,
           maths::MULTIPLE,
           CommandLength::MATH,
           maths::NUMBER_CONST,
           CommandLength::MATH,
           3,
           CommandLength::NUMBER,
           maths::NUMBER_CONST,
           CommandLength::MATH,
           4,
           CommandLength::NUMBER);
  size_t finalPos = CommandLength::MATH * 3 + CommandLength::NUMBER * 2;
  test(gen, finalPos, START_ENERGY - 3, 12);
}

// test divide parser
TEST(ParseExpression, Divide)
{
  std::vector<char> gen;

  appender(gen,
           maths::DIVIDE,
           CommandLength::MATH,
           maths::NUMBER_CONST,
           CommandLength::MATH,
           10,
           CommandLength::NUMBER,
           maths::NUMBER_CONST,
           CommandLength::MATH,
           2,
           CommandLength::NUMBER);
  size_t finalPos = CommandLength::MATH * 3 + CommandLength::NUMBER * 2;
  test(gen, finalPos, START_ENERGY - 3, 5);
}

// test rest-divide parser
TEST(ParseExpression, Rest_divide)
{
  std::vector<char> gen;

  appender(gen,
           maths::REST_DEVIDE,
           CommandLength::MATH,
           maths::NUMBER_CONST,
           CommandLength::MATH,
           11,
           CommandLength::NUMBER,
           maths::NUMBER_CONST,
           CommandLength::MATH,
           3,
           CommandLength::NUMBER);
  size_t finalPos = CommandLength::MATH * 3 + CommandLength::NUMBER * 2;
  test(gen, finalPos, START_ENERGY - 3, 2);
}

// test getting energy
TEST(ParseExpression, Energy)
{
  std::vector<char> gen;

  appender(gen, maths::ENERGY, CommandLength::MATH);
  size_t finalPos = CommandLength::MATH;
  test(gen, finalPos, START_ENERGY - 1, 99);
}

// test Answer
TEST(ParseExpression, Answer)
{
  std::vector<char> gen;
  appender(gen,
           maths::ANSWER,
           CommandLength::MATH,
           answer::Empty,
           CommandLength::ANSWER);

  size_t finalPos = CommandLength::MATH + CommandLength::ANSWER;
  test(gen, finalPos, START_ENERGY - 1, static_cast<size_t>(answer::Empty));

  gen.clear();
  appender(gen,
           maths::ANSWER,
           CommandLength::MATH,
           answer::UnitIsHere,
           CommandLength::ANSWER);
  test(
    gen, finalPos, START_ENERGY - 1, static_cast<size_t>(answer::UnitIsHere));
}

/// Bool expressions test block

void
testBool(const std::vector<char>& gen,
         const size_t resultPos,
         const long long finalEnergy,
         const bool correctResult)
{
  testGenom tgen;

  size_t next = 0;
  long long energy = START_ENERGY;
  tgen.setGenom(gen);
  bool result = tgen.testParseBoolExpression(next, energy, next);
  ASSERT_EQ(next, resultPos);
  ASSERT_EQ(result, correctResult);
  ASSERT_EQ(energy, finalEnergy);
}

// test const bool
TEST(ParseBoolExpression, Const)
{
  std::vector<char> gen;
  appender(gen,
           boolMath::BOOL_CONST,
           CommandLength::BOOL,
           false,
           CommandLength::CONST_BOOL);
  size_t finalPos = CommandLength::BOOL + CommandLength::CONST_BOOL;
  testBool(gen, finalPos, START_ENERGY - 1, false);

  gen.clear();
  appender(gen,
           boolMath::BOOL_CONST,
           CommandLength::BOOL,
           true,
           CommandLength::CONST_BOOL);
  testBool(gen, finalPos, START_ENERGY - 1, true);
}

// test and operator bool
TEST(ParseBoolExpression, And)
{
  std::vector<char> gen;
  appender(gen,
           boolMath::AND,
           CommandLength::BOOL,
           boolMath::BOOL_CONST,
           CommandLength::BOOL,
           false,
           CommandLength::CONST_BOOL,
           boolMath::BOOL_CONST,
           CommandLength::BOOL,
           true,
           CommandLength::CONST_BOOL);
  size_t finalPos = CommandLength::BOOL * 3 + CommandLength::CONST_BOOL * 2;
  testBool(gen, finalPos, START_ENERGY - 3, false);

  gen.clear();
  appender(gen,
           boolMath::AND,
           CommandLength::BOOL,
           boolMath::BOOL_CONST,
           CommandLength::BOOL,
           true,
           CommandLength::CONST_BOOL,
           boolMath::BOOL_CONST,
           CommandLength::BOOL,
           true,
           CommandLength::CONST_BOOL);
  testBool(gen, finalPos, START_ENERGY - 3, true);
}

// test or operator bool
TEST(ParseBoolExpression, Or)
{
  std::vector<char> gen;
  appender(gen,
           boolMath::OR,
           CommandLength::BOOL,
           boolMath::BOOL_CONST,
           CommandLength::BOOL,
           false,
           CommandLength::CONST_BOOL,
           boolMath::BOOL_CONST,
           CommandLength::BOOL,
           true,
           CommandLength::CONST_BOOL);
  size_t finalPos = CommandLength::BOOL * 3 + CommandLength::CONST_BOOL * 2;
  testBool(gen, finalPos, START_ENERGY - 3, true);

  gen.clear();
  appender(gen,
           boolMath::OR,
           CommandLength::BOOL,
           boolMath::BOOL_CONST,
           CommandLength::BOOL,
           false,
           CommandLength::CONST_BOOL,
           boolMath::BOOL_CONST,
           CommandLength::BOOL,
           false,
           CommandLength::CONST_BOOL);
  testBool(gen, finalPos, START_ENERGY - 3, false);
}

// test xor operator bool
TEST(ParseBoolExpression, Xor)
{
  std::vector<char> gen;
  appender(gen,
           boolMath::XOR,
           CommandLength::BOOL,
           boolMath::BOOL_CONST,
           CommandLength::BOOL,
           false,
           CommandLength::CONST_BOOL,
           boolMath::BOOL_CONST,
           CommandLength::BOOL,
           true,
           CommandLength::CONST_BOOL);
  size_t finalPos = CommandLength::BOOL * 3 + CommandLength::CONST_BOOL * 2;
  testBool(gen, finalPos, START_ENERGY - 3, true);

  gen.clear();
  appender(gen,
           boolMath::XOR,
           CommandLength::BOOL,
           boolMath::BOOL_CONST,
           CommandLength::BOOL,
           false,
           CommandLength::CONST_BOOL,
           boolMath::BOOL_CONST,
           CommandLength::BOOL,
           false,
           CommandLength::CONST_BOOL);
  testBool(gen, finalPos, START_ENERGY - 3, false);

  gen.clear();
  appender(gen,
           boolMath::XOR,
           CommandLength::BOOL,
           boolMath::BOOL_CONST,
           CommandLength::BOOL,
           true,
           CommandLength::CONST_BOOL,
           boolMath::BOOL_CONST,
           CommandLength::BOOL,
           true,
           CommandLength::CONST_BOOL);
  testBool(gen, finalPos, START_ENERGY - 3, false);
}

// test More operator bool
TEST(ParseBoolExpression, More)
{
  std::vector<char> gen;
  appender(gen,
           boolMath::MORE,
           CommandLength::BOOL,
           maths::NUMBER_CONST,
           CommandLength::MATH,
           2,
           CommandLength::NUMBER,
           maths::NUMBER_CONST,
           CommandLength::MATH,
           1,
           CommandLength::NUMBER);
  size_t finalPos =
    CommandLength::BOOL + CommandLength::MATH * 2 + CommandLength::NUMBER * 2;
  testBool(gen, finalPos, START_ENERGY - 3, true);

  gen.clear();
  appender(gen,
           boolMath::MORE,
           CommandLength::BOOL,
           maths::NUMBER_CONST,
           CommandLength::MATH,
           1,
           CommandLength::NUMBER,
           maths::NUMBER_CONST,
           CommandLength::MATH,
           2,
           CommandLength::NUMBER);
  testBool(gen, finalPos, START_ENERGY - 3, false);
}

// test Less operator bool
TEST(ParseBoolExpression, Less)
{
  std::vector<char> gen;
  appender(gen,
           boolMath::LESS,
           CommandLength::BOOL,
           maths::NUMBER_CONST,
           CommandLength::MATH,
           2,
           CommandLength::NUMBER,
           maths::NUMBER_CONST,
           CommandLength::MATH,
           1,
           CommandLength::NUMBER);
  size_t finalPos =
    CommandLength::BOOL + CommandLength::MATH * 2 + CommandLength::NUMBER * 2;
  testBool(gen, finalPos, START_ENERGY - 3, false);

  gen.clear();
  appender(gen,
           boolMath::LESS,
           CommandLength::BOOL,
           maths::NUMBER_CONST,
           CommandLength::MATH,
           1,
           CommandLength::NUMBER,
           maths::NUMBER_CONST,
           CommandLength::MATH,
           2,
           CommandLength::NUMBER);
  testBool(gen, finalPos, START_ENERGY - 3, true);
}

// test More_Equal operator bool
TEST(ParseBoolExpression, More_Equal)
{
  std::vector<char> gen;
  appender(gen,
           boolMath::MORE_EQUAL,
           CommandLength::BOOL,
           maths::NUMBER_CONST,
           CommandLength::MATH,
           2,
           CommandLength::NUMBER,
           maths::NUMBER_CONST,
           CommandLength::MATH,
           1,
           CommandLength::NUMBER);
  size_t finalPos =
    CommandLength::BOOL + CommandLength::MATH * 2 + CommandLength::NUMBER * 2;
  testBool(gen, finalPos, START_ENERGY - 3, true);

  gen.clear();
  appender(gen,
           boolMath::MORE_EQUAL,
           CommandLength::BOOL,
           maths::NUMBER_CONST,
           CommandLength::MATH,
           2,
           CommandLength::NUMBER,
           maths::NUMBER_CONST,
           CommandLength::MATH,
           2,
           CommandLength::NUMBER);
  testBool(gen, finalPos, START_ENERGY - 3, true);

  gen.clear();
  appender(gen,
           boolMath::MORE_EQUAL,
           CommandLength::BOOL,
           maths::NUMBER_CONST,
           CommandLength::MATH,
           2,
           CommandLength::NUMBER,
           maths::NUMBER_CONST,
           CommandLength::MATH,
           3,
           CommandLength::NUMBER);
  testBool(gen, finalPos, START_ENERGY - 3, false);
}

// test Less_Equal operator bool
TEST(ParseBoolExpression, Less_Equal)
{
  std::vector<char> gen;
  appender(gen,
           boolMath::LESS_EQUAL,
           CommandLength::BOOL,
           maths::NUMBER_CONST,
           CommandLength::MATH,
           2,
           CommandLength::NUMBER,
           maths::NUMBER_CONST,
           CommandLength::MATH,
           1,
           CommandLength::NUMBER);
  size_t finalPos =
    CommandLength::BOOL + CommandLength::MATH * 2 + CommandLength::NUMBER * 2;
  testBool(gen, finalPos, START_ENERGY - 3, false);

  gen.clear();
  appender(gen,
           boolMath::LESS_EQUAL,
           CommandLength::BOOL,
           maths::NUMBER_CONST,
           CommandLength::MATH,
           2,
           CommandLength::NUMBER,
           maths::NUMBER_CONST,
           CommandLength::MATH,
           2,
           CommandLength::NUMBER);
  testBool(gen, finalPos, START_ENERGY - 3, true);

  gen.clear();
  appender(gen,
           boolMath::LESS_EQUAL,
           CommandLength::BOOL,
           maths::NUMBER_CONST,
           CommandLength::MATH,
           2,
           CommandLength::NUMBER,
           maths::NUMBER_CONST,
           CommandLength::MATH,
           3,
           CommandLength::NUMBER);
  testBool(gen, finalPos, START_ENERGY - 3, true);
}

// test Equal operator bool
TEST(ParseBoolExpression, Equal)
{
  std::vector<char> gen;
  appender(gen,
           boolMath::EQUAL,
           CommandLength::BOOL,
           maths::NUMBER_CONST,
           CommandLength::MATH,
           2,
           CommandLength::NUMBER,
           maths::NUMBER_CONST,
           CommandLength::MATH,
           1,
           CommandLength::NUMBER);
  size_t finalPos =
    CommandLength::BOOL + CommandLength::MATH * 2 + CommandLength::NUMBER * 2;
  testBool(gen, finalPos, START_ENERGY - 3, false);

  gen.clear();
  appender(gen,
           boolMath::EQUAL,
           CommandLength::BOOL,
           maths::NUMBER_CONST,
           CommandLength::MATH,
           2,
           CommandLength::NUMBER,
           maths::NUMBER_CONST,
           CommandLength::MATH,
           2,
           CommandLength::NUMBER);
  testBool(gen, finalPos, START_ENERGY - 3, true);

  gen.clear();
  appender(gen,
           boolMath::EQUAL,
           CommandLength::BOOL,
           maths::NUMBER_CONST,
           CommandLength::MATH,
           2,
           CommandLength::NUMBER,
           maths::NUMBER_CONST,
           CommandLength::MATH,
           3,
           CommandLength::NUMBER);
  testBool(gen, finalPos, START_ENERGY - 3, false);
}

// test No_Equal operator bool
TEST(ParseBoolExpression, No_Equal)
{
  std::vector<char> gen;
  appender(gen,
           boolMath::NO_EQUAL,
           CommandLength::BOOL,
           maths::NUMBER_CONST,
           CommandLength::MATH,
           2,
           CommandLength::NUMBER,
           maths::NUMBER_CONST,
           CommandLength::MATH,
           1,
           CommandLength::NUMBER);
  size_t finalPos =
    CommandLength::BOOL + CommandLength::MATH * 2 + CommandLength::NUMBER * 2;
  testBool(gen, finalPos, START_ENERGY - 3, true);

  gen.clear();
  appender(gen,
           boolMath::NO_EQUAL,
           CommandLength::BOOL,
           maths::NUMBER_CONST,
           CommandLength::MATH,
           2,
           CommandLength::NUMBER,
           maths::NUMBER_CONST,
           CommandLength::MATH,
           2,
           CommandLength::NUMBER);
  testBool(gen, finalPos, START_ENERGY - 3, false);

  gen.clear();
  appender(gen,
           boolMath::NO_EQUAL,
           CommandLength::BOOL,
           maths::NUMBER_CONST,
           CommandLength::MATH,
           2,
           CommandLength::NUMBER,
           maths::NUMBER_CONST,
           CommandLength::MATH,
           3,
           CommandLength::NUMBER);
  testBool(gen, finalPos, START_ENERGY - 3, true);
}

// test No operator bool
TEST(ParseBoolExpression, No)
{
  std::vector<char> gen;
  appender(gen,
           boolMath::NO,
           CommandLength::BOOL,
           boolMath::BOOL_CONST,
           CommandLength::BOOL,
           true,
           CommandLength::CONST_BOOL);
  size_t finalPos = CommandLength::BOOL * 2 + CommandLength::CONST_BOOL;
  testBool(gen, finalPos, START_ENERGY - 2, false);

  gen.clear();
  appender(gen,
           boolMath::NO,
           CommandLength::BOOL,
           boolMath::BOOL_CONST,
           CommandLength::BOOL,
           true,
           CommandLength::CONST_BOOL);
  testBool(gen, finalPos, START_ENERGY - 2, false);
}

void
testIf(const std::vector<char>& gen,
       const long long finalEnergy,
       const bool correctResult)
{
  testGenom tgen;

  long long energy = START_ENERGY;
  tgen.setGenom(gen);
  bool result = tgen.testParseIf(energy);
  ASSERT_EQ(result, correctResult);
  ASSERT_EQ(energy, finalEnergy);
}

/// IF block
// test No operator bool
TEST(ParseIFExpression, JustBoolConsts)
{
  std::vector<char> gen;
  appender(gen,
           boolMath::MORE,
           CommandLength::BOOL, // 4
           maths::NUMBER_CONST,
           CommandLength::MATH, // 3
           5,
           CommandLength::NUMBER, // 4
           maths::NUMBER_CONST,
           CommandLength::MATH, // 3
           3,
           CommandLength::NUMBER, // 4
           20,
           CommandLength::GOTO, // 6
           10,
           CommandLength::GOTO); // 6
  testIf(gen, START_ENERGY - 3, 20);

  gen.clear();
  appender(gen,
           boolMath::LESS,
           CommandLength::BOOL, // 4
           maths::NUMBER_CONST,
           CommandLength::MATH, // 3
           5,
           CommandLength::NUMBER, // 4
           maths::NUMBER_CONST,
           CommandLength::MATH, // 3
           3,
           CommandLength::NUMBER, // 4
           20,
           CommandLength::GOTO, // 6
           10,
           CommandLength::GOTO);

  testIf(gen, START_ENERGY - 3, 10);
}
