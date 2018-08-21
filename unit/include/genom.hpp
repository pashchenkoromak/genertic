#include "operation.hpp"
#include <string>
#include <vector>
#ifndef GENOM_HPP
#define GENOM_HPP

/// @class Genom
/// @brief Genom is a sequence of 0 and 1 and parser for it.
/// @note Can parse any sequence.
class Genom
{
public:
  /// @brief constructor. It makes new genom, randomly filled commands.
  Genom();

  /// @brief default destructor
  virtual ~Genom() = default;

  /// @brief Pick one of possible mutations
  /// @result changes in genom
  virtual void mutation();

  /// @brief makes next move, due to genom.
  /// @param[out] energy - need energy for every iteration of thinking.
  /// On finish energy will be decreased due to algorithm coded in genom.
  /// @return Operation struct with command to the World.
  virtual Operation nextMove(long long& energy);

protected:
  /// @brief change count of genes
  void genomMutation();

  /// @brief small mutation of small count of genes
  void genMutation();

  /// @brief the biggest mutation
  void chromosomeMutation();

  /// @brief doubles some small part of genom
  void doubleGen();

  /// @brief erase some small part of genom
  void eraseGen();

  /// @brief reverse small part of genom
  void reverseGen();

  /// @brief parses info after goto command in genom
  /// @param[in] startPosition - genom thinks, that before it was GOTO command.
  /// @return next command position
  /// @note doesn't change m_nextCommand
  long long parseGoto(const long long startPosition);

  /// @brief parses GO command. It needs additional info - direction.
  /// @return Operation GO with direction in params.
  Operation parseGo();

  /// @brief parses MAKE_CHILD command. It for now doesn't need additional info,
  /// but it is possible.
  /// @return Operation MAKE_CHILD.
  Operation parseMakeChild();

  /// @brief Parses SEE command. Needs direction.
  /// @return Operation SEE with direction param.
  Operation parseSee();

  /// @brief Parses ATTACK command. Needs direction.
  /// @return Operation ATTACK with direction param.
  Operation parseAttack();

  /// @brief Parse IF command. See more info in operation.hpp file.
  /// @return next command position
  /// @note doesn't change m_nextCommand
  long long parseIf(long long& energy);

  /// @brief Get next operation after startCommand.
  /// @param[in] startCommand - place, where start getting
  /// @param[in] commandLength - length of command
  /// @return size_t, which can be parsed as enum from operation.hpp file.
  /// @note Be careful about commandLength!
  size_t getNextOperation(
    const size_t startCommand,
    const size_t commandLength = CommandLength::OPERATION);

  /// @brief Parses expression. See more info about it in operation.hpp file.
  /// @param[in] startCommand - here parser will start his work.
  /// @param[in, out] energy - needs for thinking. After finish - will be
  /// decreased due to algo.
  /// @param[out] next - number of next command.
  /// @return Result of expression.
  int parseExpression(const size_t startCommand,
                      long long& energy,
                      size_t& next);

  /// @brief Parses bool expression.
  /// @param[in] startCommand - here parser will start his work.
  /// @param[in, out] energy - needs for thinking. After finish - will be
  /// decreased due to algo.
  /// @param[out] next - number of next command.
  /// @return Result of expression.
  bool parseBoolExpression(const size_t startCommand,
                           long long& energy,
                           size_t& next);

  /// @brief Started size of genom (it can be a little more).
  static constexpr size_t DEFAULT_SIZE = 64;

  /// @brief Number of the next command in genom.
  size_t m_nextMoveNum = 0;

  /// @brief Sequence of 0/1 chars - genom. Any sequence is valid genom.
  std::vector<char> m_genom;
};

#endif // GENOM_HPP
