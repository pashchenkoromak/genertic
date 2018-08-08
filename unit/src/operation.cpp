#include "operation.hpp"

Operation::Operation(const operationType& _type) : type(_type) {}

bool Operation::isWorldOperation()
{
   return operationType::PHOTOSYNTESIS == type || operationType::SEE == type || operationType::GO == type;
}
