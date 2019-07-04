#include "common/common.hpp"
#include "gtest/gtest.h"

/// Bool expressions test block

void testBool(const std::vector<char>& gen, const size_t resultPos, const long long finalEnergy,
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
    appender(gen, std::make_pair(boolMath::BOOL_CONST, CommandLength::BOOL),
             std::make_pair(false, CommandLength::CONST_BOOL));
    size_t finalPos = CommandLength::BOOL + CommandLength::CONST_BOOL;
    testBool(gen, finalPos, START_ENERGY - 1, false);

    gen.clear();
    appender(gen, std::make_pair(boolMath::BOOL_CONST, CommandLength::BOOL),
             std::make_pair(true, CommandLength::CONST_BOOL));
    testBool(gen, finalPos, START_ENERGY - 1, true);
}

// test and operator bool
TEST(ParseBoolExpression, And)
{
    std::vector<char> gen;
    appender(
        gen, std::make_pair(boolMath::AND, CommandLength::BOOL),
        std::make_pair(boolMath::BOOL_CONST, CommandLength::BOOL), std::make_pair(false, CommandLength::CONST_BOOL),
        std::make_pair(boolMath::BOOL_CONST, CommandLength::BOOL), std::make_pair(true, CommandLength::CONST_BOOL));
    size_t finalPos = CommandLength::BOOL * 3 + CommandLength::CONST_BOOL * 2;
    testBool(gen, finalPos, START_ENERGY - 3, false);

    gen.clear();
    appender(gen, std::make_pair(boolMath::AND, CommandLength::BOOL),
             std::make_pair(boolMath::BOOL_CONST, CommandLength::BOOL), std::make_pair(true, CommandLength::CONST_BOOL),
             std::make_pair(boolMath::BOOL_CONST, CommandLength::BOOL),
             std::make_pair(true, CommandLength::CONST_BOOL));
    testBool(gen, finalPos, START_ENERGY - 3, true);
}

// test or operator bool
TEST(ParseBoolExpression, Or)
{
    std::vector<char> gen;
    appender(
        gen, std::make_pair(boolMath::OR, CommandLength::BOOL),
        std::make_pair(boolMath::BOOL_CONST, CommandLength::BOOL), std::make_pair(false, CommandLength::CONST_BOOL),
        std::make_pair(boolMath::BOOL_CONST, CommandLength::BOOL), std::make_pair(true, CommandLength::CONST_BOOL));
    size_t finalPos = CommandLength::BOOL * 3 + CommandLength::CONST_BOOL * 2;
    testBool(gen, finalPos, START_ENERGY - 3, true);

    gen.clear();
    appender(
        gen, std::make_pair(boolMath::OR, CommandLength::BOOL),
        std::make_pair(boolMath::BOOL_CONST, CommandLength::BOOL), std::make_pair(false, CommandLength::CONST_BOOL),
        std::make_pair(boolMath::BOOL_CONST, CommandLength::BOOL), std::make_pair(false, CommandLength::CONST_BOOL));
    testBool(gen, finalPos, START_ENERGY - 3, false);
}

// test xor operator bool
TEST(ParseBoolExpression, Xor)
{
    std::vector<char> gen;
    appender(
        gen, std::make_pair(boolMath::XOR, CommandLength::BOOL),
        std::make_pair(boolMath::BOOL_CONST, CommandLength::BOOL), std::make_pair(false, CommandLength::CONST_BOOL),
        std::make_pair(boolMath::BOOL_CONST, CommandLength::BOOL), std::make_pair(true, CommandLength::CONST_BOOL));
    size_t finalPos = CommandLength::BOOL * 3 + CommandLength::CONST_BOOL * 2;
    testBool(gen, finalPos, START_ENERGY - 3, true);

    gen.clear();
    appender(
        gen, std::make_pair(boolMath::XOR, CommandLength::BOOL),
        std::make_pair(boolMath::BOOL_CONST, CommandLength::BOOL), std::make_pair(false, CommandLength::CONST_BOOL),
        std::make_pair(boolMath::BOOL_CONST, CommandLength::BOOL), std::make_pair(false, CommandLength::CONST_BOOL));
    testBool(gen, finalPos, START_ENERGY - 3, false);

    gen.clear();
    appender(gen, std::make_pair(boolMath::XOR, CommandLength::BOOL),
             std::make_pair(boolMath::BOOL_CONST, CommandLength::BOOL), std::make_pair(true, CommandLength::CONST_BOOL),
             std::make_pair(boolMath::BOOL_CONST, CommandLength::BOOL),
             std::make_pair(true, CommandLength::CONST_BOOL));
    testBool(gen, finalPos, START_ENERGY - 3, false);
}

// test More operator bool
TEST(ParseBoolExpression, More)
{
    std::vector<char> gen;
    appender(gen, std::make_pair(boolMath::MORE, CommandLength::BOOL),
             std::make_pair(maths::NUMBER_CONST, CommandLength::MATH), std::make_pair(2, CommandLength::NUMBER),
             std::make_pair(maths::NUMBER_CONST, CommandLength::MATH), std::make_pair(1, CommandLength::NUMBER));
    size_t finalPos = CommandLength::BOOL + CommandLength::MATH * 2 + CommandLength::NUMBER * 2;
    testBool(gen, finalPos, START_ENERGY - 3, true);

    gen.clear();
    appender(gen, std::make_pair(boolMath::MORE, CommandLength::BOOL),
             std::make_pair(maths::NUMBER_CONST, CommandLength::MATH), std::make_pair(1, CommandLength::NUMBER),
             std::make_pair(maths::NUMBER_CONST, CommandLength::MATH), std::make_pair(2, CommandLength::NUMBER));
    testBool(gen, finalPos, START_ENERGY - 3, false);
}

// test Less operator bool
TEST(ParseBoolExpression, Less)
{
    std::vector<char> gen;
    appender(gen, std::make_pair(boolMath::LESS, CommandLength::BOOL),
             std::make_pair(maths::NUMBER_CONST, CommandLength::MATH), std::make_pair(2, CommandLength::NUMBER),
             std::make_pair(maths::NUMBER_CONST, CommandLength::MATH), std::make_pair(1, CommandLength::NUMBER));
    size_t finalPos = CommandLength::BOOL + CommandLength::MATH * 2 + CommandLength::NUMBER * 2;
    testBool(gen, finalPos, START_ENERGY - 3, false);

    gen.clear();
    appender(gen, std::make_pair(boolMath::LESS, CommandLength::BOOL),
             std::make_pair(maths::NUMBER_CONST, CommandLength::MATH), std::make_pair(1, CommandLength::NUMBER),
             std::make_pair(maths::NUMBER_CONST, CommandLength::MATH), std::make_pair(2, CommandLength::NUMBER));
    testBool(gen, finalPos, START_ENERGY - 3, true);
}

// test More_Equal operator bool
TEST(ParseBoolExpression, More_Equal)
{
    std::vector<char> gen;
    appender(gen, std::make_pair(boolMath::MORE_EQUAL, CommandLength::BOOL),
             std::make_pair(maths::NUMBER_CONST, CommandLength::MATH), std::make_pair(2, CommandLength::NUMBER),
             std::make_pair(maths::NUMBER_CONST, CommandLength::MATH), std::make_pair(1, CommandLength::NUMBER));
    size_t finalPos = CommandLength::BOOL + CommandLength::MATH * 2 + CommandLength::NUMBER * 2;
    testBool(gen, finalPos, START_ENERGY - 3, true);

    gen.clear();
    appender(gen, std::make_pair(boolMath::MORE_EQUAL, CommandLength::BOOL),
             std::make_pair(maths::NUMBER_CONST, CommandLength::MATH), std::make_pair(2, CommandLength::NUMBER),
             std::make_pair(maths::NUMBER_CONST, CommandLength::MATH), std::make_pair(2, CommandLength::NUMBER));
    testBool(gen, finalPos, START_ENERGY - 3, true);

    gen.clear();
    appender(gen, std::make_pair(boolMath::MORE_EQUAL, CommandLength::BOOL),
             std::make_pair(maths::NUMBER_CONST, CommandLength::MATH), std::make_pair(2, CommandLength::NUMBER),
             std::make_pair(maths::NUMBER_CONST, CommandLength::MATH), std::make_pair(3, CommandLength::NUMBER));
    testBool(gen, finalPos, START_ENERGY - 3, false);
}

// test Less_Equal operator bool
TEST(ParseBoolExpression, Less_Equal)
{
    std::vector<char> gen;
    appender(gen, std::make_pair(boolMath::LESS_EQUAL, CommandLength::BOOL),
             std::make_pair(maths::NUMBER_CONST, CommandLength::MATH), std::make_pair(2, CommandLength::NUMBER),
             std::make_pair(maths::NUMBER_CONST, CommandLength::MATH), std::make_pair(1, CommandLength::NUMBER));
    size_t finalPos = CommandLength::BOOL + CommandLength::MATH * 2 + CommandLength::NUMBER * 2;
    testBool(gen, finalPos, START_ENERGY - 3, false);

    gen.clear();
    appender(gen, std::make_pair(boolMath::LESS_EQUAL, CommandLength::BOOL),
             std::make_pair(maths::NUMBER_CONST, CommandLength::MATH), std::make_pair(2, CommandLength::NUMBER),
             std::make_pair(maths::NUMBER_CONST, CommandLength::MATH), std::make_pair(2, CommandLength::NUMBER));
    testBool(gen, finalPos, START_ENERGY - 3, true);

    gen.clear();
    appender(gen, std::make_pair(boolMath::LESS_EQUAL, CommandLength::BOOL),
             std::make_pair(maths::NUMBER_CONST, CommandLength::MATH), std::make_pair(2, CommandLength::NUMBER),
             std::make_pair(maths::NUMBER_CONST, CommandLength::MATH), std::make_pair(3, CommandLength::NUMBER));
    testBool(gen, finalPos, START_ENERGY - 3, true);
}

// test Equal operator bool
TEST(ParseBoolExpression, Equal)
{
    std::vector<char> gen;
    appender(gen, std::make_pair(boolMath::EQUAL, CommandLength::BOOL),
             std::make_pair(maths::NUMBER_CONST, CommandLength::MATH), std::make_pair(2, CommandLength::NUMBER),
             std::make_pair(maths::NUMBER_CONST, CommandLength::MATH), std::make_pair(1, CommandLength::NUMBER));
    size_t finalPos = CommandLength::BOOL + CommandLength::MATH * 2 + CommandLength::NUMBER * 2;
    testBool(gen, finalPos, START_ENERGY - 3, false);

    gen.clear();
    appender(gen, std::make_pair(boolMath::EQUAL, CommandLength::BOOL),
             std::make_pair(maths::NUMBER_CONST, CommandLength::MATH), std::make_pair(2, CommandLength::NUMBER),
             std::make_pair(maths::NUMBER_CONST, CommandLength::MATH), std::make_pair(2, CommandLength::NUMBER));
    testBool(gen, finalPos, START_ENERGY - 3, true);

    gen.clear();
    appender(gen, std::make_pair(boolMath::EQUAL, CommandLength::BOOL),
             std::make_pair(maths::NUMBER_CONST, CommandLength::MATH), std::make_pair(2, CommandLength::NUMBER),
             std::make_pair(maths::NUMBER_CONST, CommandLength::MATH), std::make_pair(3, CommandLength::NUMBER));
    testBool(gen, finalPos, START_ENERGY - 3, false);
}

// test No_Equal operator bool
TEST(ParseBoolExpression, No_Equal)
{
    std::vector<char> gen;
    appender(gen, std::make_pair(boolMath::NO_EQUAL, CommandLength::BOOL),
             std::make_pair(maths::NUMBER_CONST, CommandLength::MATH), std::make_pair(2, CommandLength::NUMBER),
             std::make_pair(maths::NUMBER_CONST, CommandLength::MATH), std::make_pair(1, CommandLength::NUMBER));
    size_t finalPos = CommandLength::BOOL + CommandLength::MATH * 2 + CommandLength::NUMBER * 2;
    testBool(gen, finalPos, START_ENERGY - 3, true);

    gen.clear();
    appender(gen, std::make_pair(boolMath::NO_EQUAL, CommandLength::BOOL),
             std::make_pair(maths::NUMBER_CONST, CommandLength::MATH), std::make_pair(2, CommandLength::NUMBER),
             std::make_pair(maths::NUMBER_CONST, CommandLength::MATH), std::make_pair(2, CommandLength::NUMBER));
    testBool(gen, finalPos, START_ENERGY - 3, false);

    gen.clear();
    appender(gen, std::make_pair(boolMath::NO_EQUAL, CommandLength::BOOL),
             std::make_pair(maths::NUMBER_CONST, CommandLength::MATH), std::make_pair(2, CommandLength::NUMBER),
             std::make_pair(maths::NUMBER_CONST, CommandLength::MATH), std::make_pair(3, CommandLength::NUMBER));
    testBool(gen, finalPos, START_ENERGY - 3, true);
}

// test No operator bool
TEST(ParseBoolExpression, No)
{
    std::vector<char> gen;
    appender(gen, std::make_pair(boolMath::NO, CommandLength::BOOL),
             std::make_pair(boolMath::BOOL_CONST, CommandLength::BOOL),
             std::make_pair(true, CommandLength::CONST_BOOL));
    size_t finalPos = CommandLength::BOOL * 2 + CommandLength::CONST_BOOL;
    testBool(gen, finalPos, START_ENERGY - 2, false);

    gen.clear();
    appender(gen, std::make_pair(boolMath::NO, CommandLength::BOOL),
             std::make_pair(boolMath::BOOL_CONST, CommandLength::BOOL),
             std::make_pair(true, CommandLength::CONST_BOOL));
    testBool(gen, finalPos, START_ENERGY - 2, false);
}
