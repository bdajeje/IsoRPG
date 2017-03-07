#include "utils/time.hpp"

namespace utils {

sf::Uint8 addTimeDiff(sf::Uint8 original, sf::Uint8 target, int elapsed_time, int total_time)
{
  const float diff_per_ms = (target - original) / static_cast<float>(total_time);
  return original + diff_per_ms * elapsed_time;
}

std::string readableTime(unsigned int mins)
{
  int hours = mins / 60;
  std::string result;

  if(hours > 0)
  {
    result += std::to_string(hours);
    mins -= hours * 60;    
    result += (mins > 0) ? "h " : " hours";
  }

  if(mins > 0)
    result += std::to_string(mins) + " mins";

  return result;
}

}
