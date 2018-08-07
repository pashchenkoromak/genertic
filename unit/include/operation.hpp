#include <string>

class Operation
{
public:
   enum operationType
   {
      GOTO,
      IF,
      PHOTOSYNTESIS,
      LOOK,
      GO,
      WHILE,
      ENERGY,
      CONST
   };
   std::string to_string(const Operation&);
};
