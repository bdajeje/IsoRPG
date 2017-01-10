#include "utils/time.hpp"

namespace utils {

sf::Uint8 addTimeDiff(sf::Uint8 original, sf::Uint8 target, int elapsed_time, int total_time)
{
  const float diff_per_ms = (target - original) / static_cast<float>(total_time);
  return original + diff_per_ms * elapsed_time;
}

}
