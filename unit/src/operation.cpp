#include "operation.hpp"


Operation::Operation(const operationType& _type) : type(_type) {}

operationType Operation::parseOperationType(const std::vector<char> &gen)
{
    size_t index = 0;
    for(auto bit : gen)
        index = (index * 2) + bit;
    return static_cast<operationType>(index);
}

bool Operation::isWorldOperation()
{
   return operationType::PHOTOSYNTESIS == type
        || operationType::SEE == type
        || operationType::GO == type
        || operationType::WAIT == type
        || operationType::MAKE_CHILD == type
        || operationType::DIE == type;
}

std::string directionToString(const directions& rhs)
{
    std::string direction;
    switch (rhs) {
        case LEFT:
            direction = "LEFT";
        break;
        case RIGHT:
            direction = "RIGHT";
        break;
        case UP:
            direction = "UP";
        break;
        case DOWN:
            direction = "DOWN";
        break;
        case UP_LEFT:
            direction = "UP_LEFT";
        break;
        case UP_RIGHT:
            direction = "UP_RIGHT";
        break;
        case DOWN_LEFT:
            direction = "DOWN_LEFT";
        break;
        case DOWN_RIGHT:
            direction = "DOWN_RIGHT";
        break;
    }
    return direction;
}
