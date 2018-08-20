#include "common/common.hpp"
#include "gtest/gtest.h"

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
// test simple if
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

// test if with expression
TEST(ParseIFExpression, Expression)
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
