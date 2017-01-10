#ifndef MATHEMATICS_HPP
#define MATHEMATICS_HPP

#include <SFML/Graphics.hpp>

namespace utils {
namespace maths {

/*! Return a random number between min (included) and max (excluded) */
int random(int min, int max);

sf::FloatRect boundsSteching(const sf::FloatRect& bounds, float strech);

}
}

#endif // MATHEMATICS_HPP
