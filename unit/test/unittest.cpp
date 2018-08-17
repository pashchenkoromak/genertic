#include <iostream>
#include "gtest/gtest.h"
#include "unit.hpp"

class testGenom : public Genom
{
public:
   testGenom() = default;
   virtual ~testGenom() = default;
   void setGenom(const std::vector<char>& rhs)
   {
       m_genom = rhs;
   }

   long long testParseGoto(){ parseGoto(); }
   Operation testParseGo(){parseGo(); }
   long long testParseIf(long long& energy) { parseIf(energy); }
   size_t testGetNextOperation(const size_t startCommand, const size_t commandLength = CommandLength::OPERATION)
   {
       getNextOperation(startCommand, commandLength);
   }
   int testParseExpression(const size_t startCommand, long long& energy, size_t& next)
   {
       parseExpression(startCommand, energy, next);
   }
   bool testParseBoolExpression(const size_t startCommand, long long& energy, size_t& next)
   {
       parseBoolExpression(startCommand, energy, next);
   }
};

const long long START_ENERGY = 100;

std::vector<char> intToChar(size_t value, const size_t length)
{
    std::vector<char> gen;
    gen.resize(length);
    for(int i = length - 1; i >=0; i--)
    {
        gen[i] = value % 2;
        value /= 2;
    }
    return gen;
}
void appendIntToChar(size_t value, std::vector<char>& vec, const size_t length)
{
    auto append = intToChar(value, length);
    vec.insert( vec.end(), append.begin(), append.end() );
}
/// ParseExpression block

void appender(std::vector<char>& vec)
{}
template<typename T_COMMAND, typename T_LENGTH, typename ... T>
void appender(std::vector<char>& vec, T_COMMAND command, T_LENGTH length, T ... args)
{
    appendIntToChar(command, vec, length);
    appender(vec, args ...);
}

// test plus parser
TEST(ParseExpression, Const) {
    testGenom tgen;
    std::vector<char> gen;

    appender(gen, maths::NUMBER_CONST, CommandLength::MATH,
      1, CommandLength::NUMBER);

    size_t next = 0;
    long long energy = START_ENERGY;
    tgen.setGenom(gen);
    int result = tgen.testParseExpression(next, energy, next);
    ASSERT_EQ(next, CommandLength::MATH + CommandLength::NUMBER);
    ASSERT_EQ(result, 1);
    ASSERT_EQ(energy, START_ENERGY - 1);
}

// test plus parser
TEST(ParseExpression, Plus) {
    testGenom tgen;
    std::vector<char> gen;

    appender(gen, maths::PLUS, CommandLength::MATH,
      maths::NUMBER_CONST, CommandLength::MATH,
      1, CommandLength::NUMBER,
      maths::NUMBER_CONST, CommandLength::MATH,
      1, CommandLength::NUMBER);

    size_t next = 0;
    long long energy = START_ENERGY;
    tgen.setGenom(gen);
    int result = tgen.testParseExpression(next, energy, next);
    ASSERT_EQ(next, CommandLength::MATH * 3 + CommandLength::NUMBER * 2);
    ASSERT_EQ(result, 2);
    ASSERT_EQ(energy, START_ENERGY - 3);
}

// test plus parser
TEST(ParseExpression, Minus) {
    testGenom tgen;
    std::vector<char> gen;

    appender(gen, maths::MINUS, CommandLength::MATH,
      maths::NUMBER_CONST, CommandLength::MATH,
      1, CommandLength::NUMBER,
      maths::NUMBER_CONST, CommandLength::MATH,
      1, CommandLength::NUMBER);

    size_t next = 0;
    long long energy = START_ENERGY;
    tgen.setGenom(gen);
    int result = tgen.testParseExpression(next, energy, next);
    ASSERT_EQ(next, CommandLength::MATH * 3 + CommandLength::NUMBER * 2);
    ASSERT_EQ(result, 0);
    ASSERT_EQ(energy, START_ENERGY - 3);
}

// test multiple parser
TEST(ParseExpression, Multiple) {
    testGenom tgen;
    std::vector<char> gen;

    appender(gen, maths::MULTIPLE, CommandLength::MATH,
      maths::NUMBER_CONST, CommandLength::MATH,
      3, CommandLength::NUMBER,
      maths::NUMBER_CONST, CommandLength::MATH,
      4, CommandLength::NUMBER);

    size_t next = 0;
    long long energy = START_ENERGY;
    tgen.setGenom(gen);
    int result = tgen.testParseExpression(next, energy, next);
    ASSERT_EQ(next, CommandLength::MATH * 3 + CommandLength::NUMBER * 2);
    ASSERT_EQ(result, 12);
    ASSERT_EQ(energy, START_ENERGY - 3);
}

// test divide parser
TEST(ParseExpression, Divide) {
    testGenom tgen;
    std::vector<char> gen;

    appender(gen, maths::DIVIDE, CommandLength::MATH,
      maths::NUMBER_CONST, CommandLength::MATH,
      10, CommandLength::NUMBER,
      maths::NUMBER_CONST, CommandLength::MATH,
      2, CommandLength::NUMBER);

    size_t next = 0;
    long long energy = START_ENERGY;
    tgen.setGenom(gen);
    int result = tgen.testParseExpression(next, energy, next);
    ASSERT_EQ(next, CommandLength::MATH * 3 + CommandLength::NUMBER * 2);
    ASSERT_EQ(result, 5);
    ASSERT_EQ(energy, START_ENERGY - 3);
}

// test rest-divide parser
TEST(ParseExpression, Rest_divide) {
    testGenom tgen;
    std::vector<char> gen;

    appender(gen, maths::REST_DEVIDE, CommandLength::MATH,
      maths::NUMBER_CONST, CommandLength::MATH,
      11, CommandLength::NUMBER,
      maths::NUMBER_CONST, CommandLength::MATH,
      3, CommandLength::NUMBER);

    size_t next = 0;
    long long energy = START_ENERGY;
    tgen.setGenom(gen);
    int result = tgen.testParseExpression(next, energy, next);
    ASSERT_EQ(next, CommandLength::MATH * 3 + CommandLength::NUMBER * 2);
    ASSERT_EQ(result, 2);
    ASSERT_EQ(energy, START_ENERGY - 3);
}

// test getting energy
TEST(ParseExpression, Energy) {
    testGenom tgen;
    std::vector<char> gen;

    appender(gen, maths::ENERGY, CommandLength::MATH);

    size_t next = 0;
    long long energy = START_ENERGY;
    tgen.setGenom(gen);
    int result = tgen.testParseExpression(next, energy, next);
    ASSERT_EQ(next, CommandLength::MATH);
    ASSERT_EQ(result, 99);
    ASSERT_EQ(energy, START_ENERGY - 1);
}
