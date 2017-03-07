#ifndef STR_HPP
#define STR_HPP

#include <string>

namespace utils {

std::string consumeUntil(std::string& input, const std::string& until, bool jump_until);
std::string readableMoney(uint money);

}

#endif // STR_HPP
