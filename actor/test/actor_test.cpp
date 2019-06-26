#include "common/common.hpp"
#include "gtest/gtest.h"

void testIf(const std::vector<char>& gen, const long long finalEnergy, const bool correctResult)
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
    appender(gen, boolMath::MORE,
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
    appender(gen, boolMath::LESS,
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
             10, CommandLength::GOTO);

    testIf(gen, START_ENERGY - 3, 10);
}

void testNextTurn(const std::vector<char>& gen, const long long finalEnergy, const Operation& correctResult)
{
    testGenom tgen;

    long long energy = START_ENERGY;
    tgen.setGenom(gen);
    Operation result = tgen.nextMove(energy);
    ASSERT_EQ(result, correctResult);
    ASSERT_EQ(energy, finalEnergy);
}

// test if with expression
TEST(ParseEndless, Must_Die)
{
    std::vector<char> gen;
    appender(gen, operationType::GOTO, CommandLength::OPERATION, 0, CommandLength::NUMBER);
    Operation die;
    die.type = operationType::DIE;
    testNextTurn(gen, 0, die);
}
