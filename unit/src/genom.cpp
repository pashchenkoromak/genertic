#include "genom.hpp"

Operation Genom::nextMove()
{
   Operation doNow;
   while (!doNow.isWorldOperation())
   {
      auto first = m_genom.begin() + m_nextMoveNum;
      auto last = m_genom.begin() + m_nextMoveNum + CommandLength::OPERATION;
      std::vector<bool> subVec(first, last);
      operationType type = Operation::parseOperationType(subVec);
      switch (type)
      {
         case operationType::GOTO:
            m_nextMoveNum += parseGoto();
            break;
         default:
            doNow.type = operationType::PHOTOSYNTESIS;
            m_nextMoveNum++;
      }
   }
   return doNow;
}

long long Genom::parseGoto()
{
   size_t length = 0;
   for (size_t i = m_nextMoveNum + CommandLength::OPERATION; i < m_nextMoveNum + CommandLength::OPERATION + CommandLength::GOTO; i++)
   {
      length = length * 2 + m_genom[i];
   }
   size_t where = 0;
   for (size_t i = m_nextMoveNum + CommandLength::OPERATION + CommandLength::GOTO;
        i < m_nextMoveNum + CommandLength::OPERATION + CommandLength::GOTO + length;
        i++)
   {
      where = where * 2 + m_genom[i];
   }
   return where;
}
