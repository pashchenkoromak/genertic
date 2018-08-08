#include "operation.hpp"
#include <string>
#include <vector>

class Genom
{
public:
   Genom();
   /// @brief inverse randomly chosen bit
   void mutation();
   Operation nextMove();

private:
   uint m_nextMoveNum;
   std::vector<bool> m_genom;
};
