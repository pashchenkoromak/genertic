#include "common/common.hpp"
#include "gtest/gtest.h"

void testExpression(const std::vector<char>& gen, const size_t resultPos, const long long finalEnergy,
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
    appender(gen, std::make_pair(maths::NUMBER_CONST, CommandLength::MATH), std::make_pair(1, CommandLength::NUMBER));
    testExpression(gen, CommandLength::MATH + CommandLength::NUMBER, START_ENERGY - 1, 1);
}

// test plus parser
TEST(ParseExpression, Plus)
{
    std::vector<char> gen;
    appender(gen, std::make_pair(maths::PLUS, CommandLength::MATH),
             std::make_pair(maths::NUMBER_CONST, CommandLength::MATH), std::make_pair(1, CommandLength::NUMBER),
             std::make_pair(maths::NUMBER_CONST, CommandLength::MATH), std::make_pair(1, CommandLength::NUMBER));
    size_t finalPos = CommandLength::MATH * 3 + CommandLength::NUMBER * 2;
    testExpression(gen, finalPos, START_ENERGY - 3, 2);
}

// test plus parser
TEST(ParseExpression, Minus)
{
    std::vector<char> gen;
    appender(gen, std::make_pair(maths::MINUS, CommandLength::MATH),
             std::make_pair(maths::NUMBER_CONST, CommandLength::MATH), std::make_pair(1, CommandLength::NUMBER),
             std::make_pair(maths::NUMBER_CONST, CommandLength::MATH), std::make_pair(1, CommandLength::NUMBER));
    size_t finalPos = CommandLength::MATH * 3 + CommandLength::NUMBER * 2;
    testExpression(gen, finalPos, START_ENERGY - 3, 0);
}

// test multiple parser
TEST(ParseExpression, Multiple)
{
    std::vector<char> gen;

    appender(gen, std::make_pair(maths::MULTIPLE, CommandLength::MATH),
             std::make_pair(maths::NUMBER_CONST, CommandLength::MATH), std::make_pair(3, CommandLength::NUMBER),
             std::make_pair(maths::NUMBER_CONST, CommandLength::MATH), std::make_pair(4, CommandLength::NUMBER));
    size_t finalPos = CommandLength::MATH * 3 + CommandLength::NUMBER * 2;
    testExpression(gen, finalPos, START_ENERGY - 3, 12);
}

// test divide parser
TEST(ParseExpression, Divide)
{
    std::vector<char> gen;

    appender(gen, std::make_pair(maths::DIVIDE, CommandLength::MATH),
             std::make_pair(maths::NUMBER_CONST, CommandLength::MATH), std::make_pair(10, CommandLength::NUMBER),
             std::make_pair(maths::NUMBER_CONST, CommandLength::MATH), std::make_pair(2, CommandLength::NUMBER));
    size_t finalPos = CommandLength::MATH * 3 + CommandLength::NUMBER * 2;
    testExpression(gen, finalPos, START_ENERGY - 3, 5);
}

// test rest-divide parser
TEST(ParseExpression, Rest_divide)
{
    std::vector<char> gen;

    appender(gen, std::make_pair(maths::REST_DEVIDE, CommandLength::MATH),
             std::make_pair(maths::NUMBER_CONST, CommandLength::MATH), std::make_pair(11, CommandLength::NUMBER),
             std::make_pair(maths::NUMBER_CONST, CommandLength::MATH), std::make_pair(3, CommandLength::NUMBER));
    size_t finalPos = CommandLength::MATH * 3 + CommandLength::NUMBER * 2;
    testExpression(gen, finalPos, START_ENERGY - 3, 2);
}

// test getting energy
TEST(ParseExpression, Energy)
{
    std::vector<char> gen;

    appender(gen, std::make_pair(maths::ENERGY, CommandLength::MATH));
    size_t finalPos = CommandLength::MATH;
    testExpression(gen, finalPos, START_ENERGY - 1, 99);
}

// test Answer
TEST(ParseExpression, Answer)
{
    std::vector<char> gen;
    appender(gen, std::make_pair(maths::ANSWER, CommandLength::MATH),
             std::make_pair(answer::Empty, CommandLength::ANSWER));

    size_t finalPos = CommandLength::MATH + CommandLength::ANSWER;
    testExpression(gen, finalPos, START_ENERGY - 1, static_cast<size_t>(answer::Empty));

    gen.clear();
    appender(gen, std::make_pair(maths::ANSWER, CommandLength::MATH),
             std::make_pair(answer::ActorIsHere, CommandLength::ANSWER));
    testExpression(gen, finalPos, START_ENERGY - 1, static_cast<size_t>(answer::ActorIsHere));
}
