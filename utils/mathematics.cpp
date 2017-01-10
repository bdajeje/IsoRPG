#include "mathematics.hpp"

#include <stdlib.h>

namespace utils {
namespace maths {

int random(int min, int max)
{
  return rand() % (max - min) + min;
}

sf::FloatRect boundsSteching(const sf::FloatRect& bounds, float strech)
{
  sf::FloatRect streched_bounds = bounds;
  streched_bounds.width += strech;
  streched_bounds.height += strech;
  return streched_bounds;
}

}
}
