#include "button.hpp"
#include "utils/graphics.hpp"
#include "managers/texture_manager.hpp"
#include "graphics/mouse.hpp"

namespace graphics {

Button::Button(const std::string& text)
  : _padding {20}
{  
  _background = getSprite("button_background.png", 1, 1);
  _text = getText("conversation.ttf", text, 20, sf::Color::Black);
  resize();
}

void Button::resize()
{
  utils::graphics::resize(_background, _text->getGlobalBounds().width + _padding, _text->getGlobalBounds().height + _padding); // \todo +20 is a hack, don't know why sfml::Text::height is heigher than usual
}

void Button::setPosition(float x, float y)
{
  _background->setPosition(x, y);
  auto bg_pos = _background->getPosition();
  auto bg_bounds = _background->getGlobalBounds();
  auto text_bounds = _text->getGlobalBounds();
  _text->setPosition(bg_pos.x + (bg_bounds.width - text_bounds.width) / 2, bg_pos.y/* + _padding / 2*/);
}

void Button::internalDraw(sf::RenderTarget& target, sf::RenderStates states) const noexcept
{
  _background->draw(target, states);
  _text->draw(target, states);
}

void Button::hover()
{
  _background->setTexture( texture::TextureManager::get("button_background_hover.png") );
  resize();
  Mouse::setStatus(Mouse::Status::Hover);
}

void Button::unhover()
{
  _background->setTexture( texture::TextureManager::get("button_background.png") );
  resize();
  Mouse::setStatus(Mouse::Status::Normal);
}

sf::FloatRect Button::getGlobalBounds() const
{
//  auto bounds = _background->getGlobalBounds();
  return _background->getGlobalBounds();
}

void Button::setColor(const sf::Color &color)
{
  _background->setColor(color);
  _text->setColor(color);
}

}
