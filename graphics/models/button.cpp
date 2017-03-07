#include "button.hpp"
#include "utils/graphics.hpp"
#include "managers/texture_manager.hpp"
#include "managers/font_manager.hpp"
#include "graphics/mouse.hpp"

namespace graphics {

Button::Button(const std::string& text, const graphics::TextProperties& text_props)
  : _background_texture {&texture::TextureManager::get("button_background.png")}
  , _background_texture_hover {&texture::TextureManager::get("button_background_hover.png")}
{  
  _text = getText("conversation.ttf", text, 20, sf::Color::Black);
  setTextProperties(text_props);

  auto bounds = _text->getGlobalBounds();
  bounds.width += 60;
  bounds.height += 15;
  _background = std::make_shared<Sprite>(bounds.width, bounds.height);
  _transformable = _background->sprite();
  _background->setTexture(*_background_texture);
}

void Button::setPosition(float x, float y)
{
  _background->setPosition(x, y);
  auto bg_pos = _background->getPosition();
  auto bg_bounds = _background->getGlobalBounds();
  auto text_bounds = _text->getGlobalBounds();
  _text->setPosition(bg_pos.x + (bg_bounds.width - text_bounds.width) / 2, bg_pos.y + (bg_bounds.height - text_bounds.height) / 2 - 9);
}

void Button::internalDraw(sf::RenderTarget& target, sf::RenderStates states) const noexcept
{
  _background->draw(target, states);
  _text->draw(target, states);
}

void Button::hover()
{
  _background->setTexture(*_background_texture_hover);
  Mouse::setStatus(Mouse::Status::Hover);
}

void Button::unhover()
{
  _background->setTexture(*_background_texture);
  Mouse::setStatus(Mouse::Status::Normal);
}

sf::FloatRect Button::getGlobalBounds() const
{
//  auto bounds = _background->getGlobalBounds();
  return _background->getGlobalBounds();
}

void Button::setColor(const sf::Color &color)
{
//  _background->setColor(color);
  _text->setColor(color);
}

void Button::setTextProperties(const graphics::TextProperties& text_props)
{
  _text->setColor(text_props.color);
  _text->setFont(font::FontManager::get(text_props.font));
  _text->setCharacterSize(text_props.size);
}

}
