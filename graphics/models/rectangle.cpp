#include "rectangle.hpp"

namespace graphics {

Rectangle::Rectangle()
  : _shape {std::make_shared<sf::RectangleShape>()}
{
  _transformable = _shape;
}

void Rectangle::internalDraw(sf::RenderTarget& target, sf::RenderStates states) const noexcept
{
  target.draw(*_shape, states);
}

}
