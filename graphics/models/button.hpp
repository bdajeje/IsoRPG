#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "graphics/drawable.hpp"
#include "graphics/text.hpp"
#include "graphics/sprite.hpp"

namespace graphics {

class Button final : public Drawable
{
  public:

    Button(const std::string& text, const TextProperties& text_props);

    virtual void setPosition(float x, float y) override;
    virtual sf::FloatRect getGlobalBounds() const override;
    virtual void setColor(const sf::Color& color) override;
    virtual const sf::Color getColor() const override { return _background->getColor(); }   

    virtual void hover() override;
    virtual void unhover() override;

  protected:

    virtual void internalDraw(sf::RenderTarget& target, sf::RenderStates states) const noexcept;
    void setTextProperties(const graphics::TextProperties& text_props);

  private:

    TextSP _text;
    SpriteSP _background;
    const sf::Texture* _background_texture;
    const sf::Texture* _background_texture_hover;
};

using ButtonSP = std::shared_ptr<Button>;

}

#endif // BUTTON_HPP
