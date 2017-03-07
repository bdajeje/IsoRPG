#ifndef FILLBAR_HPP
#define FILLBAR_HPP

#include "graphics/drawable.hpp"
#include "graphics/models/rectangle.hpp"

namespace graphics {

class FillBar : public Drawable
{
  public:

    FillBar(uint value, uint max_value, const sf::Color& fill_color, const sf::Color& outer_color, float width, float height);

    sf::FloatRect getGlobalBounds() const override { return _outer_rect->getGlobalBounds(); }

    virtual void setPosition(float x, float y) override;
    void setValue(uint value);
    void setValues(uint value, uint max_value);
    uint value() const noexcept { return _value; }
    uint maxValue() const noexcept { return _max_value; }    

    void setBackgroundColor(const sf::Color& color);
    virtual void setColor(const sf::Color& color) override;
    virtual const sf::Color getColor() const override;

  protected:

    virtual void internalDraw(sf::RenderTarget& target, sf::RenderStates states) const noexcept;    

  protected:

    RectangleSP _inner_rect;
    RectangleSP _outer_rect;
    uint _value;
    uint _max_value;    
};

using FillBarSP = std::shared_ptr<FillBar>;

}

#endif // FILLBAR_HPP
