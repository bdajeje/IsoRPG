#ifndef MENU_HPP
#define MENU_HPP

#include "graphics/drawable.hpp"
#include "graphics/sprite.hpp"
#include "graphics/text.hpp"
#include "game/events/handler.hpp"

namespace graphics {

struct MenuItem
{
  TextSP text;
  game::events::EventAction return_code;
  std::function<void()> func;
};

using MenuItemSP = std::shared_ptr<MenuItem>;

class Menu final : public Drawable
{
  public:

    Menu(int width, int height, int text_y_offset, const TextProperties& properties, const std::string& background_texture = "");

    void addItem(const std::string& text, game::events::EventAction return_code, std::function<void()> func);

    virtual sf::FloatRect getGlobalBounds() const override { return _background->getGlobalBounds(); }
    virtual void setColor(const sf::Color& /*color*/) override {}
    virtual const sf::Color getColor() const override { return sf::Color::Black; }

  protected:

    virtual void internalDraw(sf::RenderTarget& target, sf::RenderStates states) const noexcept override;

  private:

    int _text_y_offset;
    SpriteSP _background;
    std::vector<MenuItemSP> _items;
    TextProperties _properties;
};

using MenuSP = std::shared_ptr<Menu>;

}

#endif // MENU_HPP
