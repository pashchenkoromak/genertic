#include <string>
#include <vector>

namespace CommandLength {
const uint GOTO = 6;
const uint ANSWER = 1;
const uint NUMBER = 4;
const uint OPERATION = 6;
} // namespace CommandLength

/// @brief list of possible answers by world
enum answer
{
   Empty,
   Unit
};

enum operationType
{
   GOTO,
   IF,
   BOOL,
   LESS,
   MORE,
   EQUAL,
   NO_EQUAL,
   NO,
   LESS_EQUAL,
   MORE_EQUAL,
   EXPESSION,
   PLUS,
   MINUS,
   CONST,
   TRUE,
   FALSE,
   AND,
   OR,
   PHOTOSYNTESIS,
   SEE,
   GO,
   WHILE,
   ENERGY
};

struct Operation
{
   Operation();
   Operation(const operationType&);
   /// @brief Get operation type, which is coded into vector
   /// @param[in] gen - sequence of bits
   /// @return type of operation
   static operationType parseOperationType(const std::vector<bool>& gen);
   operationType type;
   std::vector<std::string> params;
};
