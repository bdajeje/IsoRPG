#ifndef FILLBAR_HPP
#define FILLBAR_HPP

#include "graphics/drawable.hpp"
#include "game/transformable.hpp"
#include "graphics/models/rectangle.hpp"

namespace graphics {

class FillBar final : public Drawable
                    , public game::Transformable
{
  public:

    FillBar(uint value, uint max_value, const sf::Color& fill_color, const sf::Color& outer_color, float width,  float height);

    sf::FloatRect getGlobalBounds() const { return _outer_rect->getGlobalBounds(); }

    void setPosition(float x, float y);
    void setPosition(const sf::Vector2f& position) { setPosition(position.x, position.y); }
    void setValue(uint value);
    uint value() const noexcept { return _value; }

    virtual void setColor(const sf::Color& color) override;
    virtual const sf::Color getColor() const override;

  protected:

    virtual void internalDraw(sf::RenderTarget& target, sf::RenderStates states) const noexcept;    

  private:

    RectangleSP _inner_rect;
    RectangleSP _outer_rect;
    uint _value;
    uint _max_value;
};

using FillBarSP = std::shared_ptr<FillBar>;

}

#endif // FILLBAR_HPP
