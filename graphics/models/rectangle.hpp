#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include <SFML/Graphics.hpp>
#include "graphics/drawable.hpp"
#include "game/transformable.hpp"

namespace graphics {

class Rectangle : public Drawable
                , public game::Transformable
{
  public:

    Rectangle();

    sf::FloatRect getGlobalBounds() const { return _shape->getGlobalBounds(); }
    std::shared_ptr<sf::RectangleShape>& shape() noexcept { return _shape; }

    virtual void setColor(const sf::Color& color) override { _shape->setFillColor(color); }
    virtual const sf::Color getColor() const override { return _shape->getFillColor(); }

  protected:

    virtual void internalDraw(sf::RenderTarget& target, sf::RenderStates states) const noexcept;

  private:

    std::shared_ptr<sf::RectangleShape> _shape;
};

using RectangleSP = std::shared_ptr<Rectangle>;

}

#endif // RECTANGLE_HPP
