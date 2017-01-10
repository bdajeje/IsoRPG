#include "fill_bar.hpp"

#include <iostream>

namespace graphics {

FillBar::FillBar(uint value, uint max_value, const sf::Color& fill_color, const sf::Color& outer_color, float width, float height)
  : _inner_rect {std::make_shared<Rectangle>()}
  , _outer_rect {std::make_shared<Rectangle>()}
  , _max_value {max_value}
{
  _transformable = _outer_rect->shape();

  _inner_rect->shape()->setFillColor(fill_color);
  _outer_rect->shape()->setOutlineColor(outer_color);
  _outer_rect->shape()->setOutlineThickness(1);
  _outer_rect->shape()->setFillColor(sf::Color{0, 0, 0, 0});

  _outer_rect->shape()->setSize({width, height});

  setValue(value);
}

void FillBar::setValue(uint value)
{
  _value = value;
  _inner_rect->shape()->setSize({_outer_rect->shape()->getGlobalBounds().width * value / 100,
                                _outer_rect->shape()->getGlobalBounds().height - 2});
}

void FillBar::internalDraw(sf::RenderTarget& target, sf::RenderStates states) const noexcept
{
  target.draw(*_outer_rect->shape(), states);
  target.draw(*_inner_rect->shape(), states);
}

void FillBar::setPosition(float x, float y)
{
  _outer_rect->setPosition(x, y);
  _inner_rect->setPosition(x, y);
}

void FillBar::setColor(const sf::Color& color)
{
  auto inner_color = _inner_rect->getColor();
  inner_color.a = color.a;
  _inner_rect->setColor(inner_color);

  auto outer_color = _outer_rect->getColor();
  outer_color.a = color.a;
  _outer_rect->setColor(outer_color);
}

const sf::Color FillBar::getColor() const
{
  return _inner_rect->getColor();
}

}
