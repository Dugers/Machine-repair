#include "relationship_wrapper.h"

initializer_is_empty::initializer_is_empty(const char* Message) : std::runtime_error{Message} {}
initializer_is_empty::initializer_is_empty(const std::string& Message) : std::runtime_error{Message} {}

