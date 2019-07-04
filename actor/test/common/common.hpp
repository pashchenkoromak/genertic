#include "actor.hpp"

#ifndef COMMON_HPP
#define COMMON_HPP

class testGenom : public Genom
{
public:
    testGenom() = default;
    virtual ~testGenom() = default;

    void setGenom(const std::vector<char>& rhs) { m_genom = rhs; }

    long long testParseIf(long long& energy) { parseIf(energy); }

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

void appendIntToChar(size_t value, std::vector<char>& vec, const size_t length);
/// ParseExpression block

void appender(std::vector<char>& vec);
template <typename T_COMMAND, typename T_LENGTH, typename... T>
void appender(std::vector<char>& vec, std::pair<T_COMMAND, T_LENGTH> command, T... args)
{
    appendIntToChar(static_cast<size_t>(command.first), vec, command.second);
    appender(vec, args...);
}

#endif // COMMON_HPP
