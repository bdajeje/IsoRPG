#include "str.hpp"

namespace utils {

std::string consumeUntil(std::string& input, const std::string& until, bool jump_until)
{
  size_t offset = input.find(until);
  if(offset == std::string::npos)
    return input;

  std::string result = input.substr(0, offset);

  if(jump_until)
    offset += until.length();

  input = input.substr(offset);

  return result;
}

}
