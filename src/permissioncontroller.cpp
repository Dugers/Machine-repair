#include "permissioncontroller.h"

permission_error::permission_error(const char* Message) : std::runtime_error{Message} {}
permission_error::permission_error(const std::string& Message) : std::runtime_error{Message} {}
