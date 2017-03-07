#include "rectangle.hpp"

namespace graphics {

Rectangle::Rectangle()
  : Rectangle{0, 0}
{}

Rectangle::Rectangle(float width, float height, const sf::Color& color)
  : _shape {std::make_shared<sf::RectangleShape>()}
{
  _transformable = _shape;
  _shape->setSize(sf::Vector2f{width, height});
  _shape->setFillColor(color);
}

void Rectangle::internalDraw(sf::RenderTarget& target, sf::RenderStates states) const noexcept
{
  target.draw(*_shape, states);
}

}
