#ifndef UTILETIME_HPP
#define UTILETIME_HPP

#include <SFML/System.hpp>
#include <chrono>

namespace utils {

  sf::Uint8 addTimeDiff(sf::Uint8 original, sf::Uint8 target, int elapsed_time, int total_time);
  std::string readableTime(unsigned int minutes);

}

#endif // UTILETIME_HPP
