#include "operation.hpp"
#include <string>
#include <vector>

class Genom
{
public:
   Genom();
   /// @brief inverse randomly chosen bit
   void mutation();
   Operation nextMove(long long& energy);

private:
   long long parseGoto();
   Operation parseGo();
   long long parseIf(long long& energy);
   size_t getNextOperation(const size_t startCommand, const size_t commandLength = CommandLength::OPERATION);
   int parseExpression(const size_t startCommand, long long& energy, size_t& next);
   bool parseBoolExpression(const size_t startCommand, long long& energy, size_t& next);
   std::pair<int, int> getTwoNumbers(size_t& next);
   static constexpr size_t DEFAULT_SIZE = 64;
   size_t m_nextMoveNum;
   std::vector<bool> m_genom;
};
