#include "genom.hpp"

Genom::Genom()
{
    m_genom.resize(Genom::DEFAULT_SIZE);
    for(size_t i = 0; i < Genom::DEFAULT_SIZE; i++)
        m_genom[i] = rand() % 2;
}

Operation Genom::nextMove(long long& energy)
{
   Operation doNow;
   while (!doNow.isWorldOperation() && energy > 0)
   {
      auto first = m_genom.begin() + m_nextMoveNum;
      auto last = m_genom.begin() + m_nextMoveNum + CommandLength::OPERATION;
      std::vector<bool> subVec(first, last);
      operationType type = Operation::parseOperationType(subVec);
      doNow.type = type;
      switch (type)
      {
         case GOTO:
            m_nextMoveNum += parseGoto();
            break;
         case PHOTOSYNTESIS:
            m_nextMoveNum++;
            break;
         case WAIT:
            m_nextMoveNum++;
            break;
         case GO:
            m_nextMoveNum++;
            parseGo();
         default:
            doNow.type = operationType::PHOTOSYNTESIS;
            m_nextMoveNum++;
      }
      energy--;
   }
   if (energy)
       return doNow;
   else return operationType::DIE;
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

Operation Genom::parseGo()
{
    size_t direction = 0;
    for (size_t i = m_nextMoveNum + CommandLength::OPERATION; i < m_nextMoveNum + CommandLength::OPERATION + CommandLength::DIRECTION; i++)
    {
       direction = direction * 2 + m_genom[i];
    }
    Operation doNow;
    doNow.params.push_back(directionToString(static_cast<directions>(direction)));
    return doNow;
}

