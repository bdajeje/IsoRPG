#ifndef UTILETIME_HPP
#define UTILETIME_HPP

#include <SFML/System.hpp>

namespace utils {

  sf::Uint8 addTimeDiff(sf::Uint8 original, sf::Uint8 target, int elapsed_time, int total_time);

}

#endif // UTILETIME_HPP
