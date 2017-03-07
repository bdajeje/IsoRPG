#ifndef CONTAINER_HPP
#define CONTAINER_HPP

#include <SFML/Graphics.hpp>

#include "graphics/sprite.hpp"
#include "graphics/drawable.hpp"
#include "graphics/models/rectangle.hpp"
#include "graphics/sprite.hpp"

namespace graphics {

struct ContainerProps {
    sf::Color bg_color = sf::Color::Black;
};

class Container : public Drawable
{
  public:

    Container(int width, int height, const sf::Vector2f& pos, ContainerProps props = {});

    virtual sf::FloatRect getGlobalBounds() const { return _background->getGlobalBounds(); }
    virtual void setColor(const sf::Color& color) { _background->setColor(color); }
    virtual const sf::Color getColor() const { return _background->getColor(); }

    virtual void setPosition(float x, float y) override;
    virtual void move(float offsetX, float y) override;

    void addDrawable(DrawableSP drawable, const sf::Vector2f& pos);
//    void setBackground();

    virtual void clicked(int x, int y) override;

  protected:

    virtual void internalDraw(sf::RenderTarget& target, sf::RenderStates states) const noexcept;
    void moveElements(float offsetX, float y);

  protected:

    std::vector<DrawableSP> _drawables;
//    DrawableSP _background;
    RectangleSP _background;
    int _width;
    int _height;
};

using ContainerSP = std::shared_ptr<Container>;

}

#endif // CONTAINER_HPP
