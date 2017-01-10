#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "graphics/drawable.hpp"
#include "graphics/text.hpp"
#include "graphics/sprite.hpp"
#include "game/transformable.hpp"

namespace graphics {

class Button final : public Drawable
                   , public game::Transformable
{
  public:

    Button(const std::string& text);

    virtual void setPosition(float x, float y) override;
    virtual void setPosition(const sf::Vector2f& position) override { setPosition(position.x, position.y); }
    virtual sf::FloatRect getGlobalBounds() const override;
    virtual void setColor(const sf::Color& color) override;
    virtual const sf::Color getColor() const override { return _background->getColor(); }

    void hover();
    void unhover();

  protected:

    virtual void internalDraw(sf::RenderTarget& target, sf::RenderStates states) const noexcept;

  private:

    void resize();

  private:

    TextSP _text;
    SpriteSP _background;
    int _padding {0};
};

using ButtonSP = std::shared_ptr<Button>;

}

#endif // BUTTON_HPP
