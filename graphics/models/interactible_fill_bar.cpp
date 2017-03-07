#include "interactible_fill_bar.hpp"

namespace graphics {

InteractibleFillBar::InteractibleFillBar(uint value, uint max_value, const sf::Color& fill_color, const sf::Color& outer_color, const sf::Color& hover_outer_color, float width, float height)
  : FillBar {value, max_value, fill_color, outer_color, width, height}
  , _hover_outer_color {hover_outer_color}
  , _default_outer_color {outer_color}
{

}

void InteractibleFillBar::clicked(int x, int /*y*/)
{
  // Transform to local coordinates
  x = x - getPosition().x;

  int value = x * _max_value / getGlobalBounds().width;
  setValue(value);
}

void InteractibleFillBar::hover()
{
  _outer_rect->shape()->setOutlineColor(_hover_outer_color);
}

void InteractibleFillBar::unhover()
{
  _outer_rect->shape()->setOutlineColor(_default_outer_color);
}

}
