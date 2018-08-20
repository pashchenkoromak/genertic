#include "operation.hpp"
#include <string>
#include <vector>
#ifndef GENOM_HPP
#define GENOM_HPP

class Genom
{
public:
  Genom();
  virtual ~Genom() = default;
  /// @brief inverse randomly chosen bit
  void mutation();
  Operation nextMove(long long& energy);

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

  /// @return next command position
  /// @note doesn't change m_nextCommand
  long long parseGoto(const long long startPosition);
  Operation parseGo();
  Operation parseMakeChild();
  Operation parseSee();
  Operation parseAttack();

  /// @return next command position
  /// @note doesn't change m_nextCommand
  long long parseIf(long long& energy);
  size_t getNextOperation(
    const size_t startCommand,
    const size_t commandLength = CommandLength::OPERATION);
  int parseExpression(const size_t startCommand,
                      long long& energy,
                      size_t& next);
  bool parseBoolExpression(const size_t startCommand,
                           long long& energy,
                           size_t& next);
  static constexpr size_t DEFAULT_SIZE = 64;
  size_t m_nextMoveNum = 0;
  std::vector<char> m_genom;
};

#endif // GENOM_HPP
