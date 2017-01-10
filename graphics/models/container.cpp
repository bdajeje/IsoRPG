#include "container.hpp"
#include "managers/texture_manager.hpp"

namespace graphics {
namespace model {

Container::Container(sf::Vector2f size_percentage, sf::Vector2f position)
{  
  const float borders_width {20};
  const float borders_height {20};

  _sprites[TopLeft]     = graphics::getSprite("container_top_left", borders_width, borders_height);
  _sprites[Top]         = graphics::getSprite("container_top", size_percentage.x, borders_height);
  _sprites[TopRight]    = graphics::getSprite("container_top_right", borders_width, borders_height);
  _sprites[Left]        = graphics::getSprite("container_left", borders_width, size_percentage.y);
  _sprites[Right]       = graphics::getSprite("container_right", borders_width, size_percentage.y);
  _sprites[BottomLeft]  = graphics::getSprite("container_bottom_left", borders_width, borders_height);
  _sprites[Bottom]      = graphics::getSprite("container_bottom", borders_width, size_percentage.x);
  _sprites[BottomRight] = graphics::getSprite("container_bottom_right", borders_width, borders_height);

  setPosition(position);
}

void Container::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  for(const SpriteSP& sprite : _sprites)
    sprite->draw(target, states);
}

void Container::setPosition(const sf::Vector2f& position) noexcept
{
  _sprites[TopLeft]->setPosition(position);
  _sprites[Top]->setPosition(_sprites[TopLeft]->getPosition().x + _sprites[TopLeft]->getLocalBounds().width, position.y);
  _sprites[TopRight]->setPosition(_sprites[Top]->getPosition().x + _sprites[Top]->getLocalBounds().width, position.y);

  _sprites[Left]->setPosition(position.x, position.y + _sprites[TopLeft]->getLocalBounds().height);
  _sprites[Right]->setPosition(_sprites[TopRight]->getPosition().x, position.y + _sprites[TopRight]->getLocalBounds().height);

  _sprites[BottomLeft]->setPosition(position.x, _sprites[Left]->getLocalBounds().height + _sprites[Left]->getLocalBounds().height);
  _sprites[Bottom]->setPosition(_sprites[BottomLeft]->getPosition().x + _sprites[BottomLeft]->getLocalBounds().width, _sprites[Right]->getPosition().y + _sprites[Right]->getLocalBounds().height);
  _sprites[BottomLeft]->setPosition(_sprites[Right]->getPosition().x, _sprites[Right]->getLocalBounds().height + _sprites[Right]->getLocalBounds().height);
}

}
}
