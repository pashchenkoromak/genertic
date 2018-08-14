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
   static constexpr size_t DEFAULT_SIZE = 64;
   size_t m_nextMoveNum;
   std::vector<bool> m_genom;
};
