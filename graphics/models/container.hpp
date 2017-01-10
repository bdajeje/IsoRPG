#ifndef CONTAINER_HPP
#define CONTAINER_HPP

#include <SFML/Graphics.hpp>

#include "graphics/sprite.hpp"

namespace graphics {
namespace model {

enum Sprites {
  TopLeft,
  Top,
  TopRight,
  Left,
  Right,
  BottomLeft,
  Bottom,
  BottomRight
};

class Container : public sf::Drawable
{
  public:

    Container(sf::Vector2f size_percentage, sf::Vector2f position);

    void setPosition(const sf::Vector2f& position) noexcept;

  protected:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

  protected:

    // \todo get array size by template?
    std::array<SpriteSP, 8> _sprites;
};

using ContainerSP = std::shared_ptr<Container>;

}
}

#endif // CONTAINER_HPP
