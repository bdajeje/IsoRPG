#include "menu.hpp"

#include "utils/graphics.hpp"
#include "managers/texture_manager.hpp"

namespace graphics {

Menu::Menu(int width, int height, int text_y_offset, const TextProperties& properties, const std::string& background_texture)
  : _text_y_offset {text_y_offset}
  , _properties {properties}
{
  _background = std::make_shared<Sprite>(width, height);
  _transformable = _background->sprite();

  if(!background_texture.empty())
    _background->setTexture(texture::TextureManager::get(background_texture));
}

void Menu::internalDraw(sf::RenderTarget& target, sf::RenderStates states) const noexcept
{
  if(_background)
    _background->draw(target, states);

  for(const auto& item : _items)
    item->text->draw(target, states);
}

void Menu::addItem(const std::string& text, game::events::EventAction return_code, std::function<void()> func)
{
  MenuItemSP item = std::make_shared<MenuItem>();
  item->text = getText(_properties.font, text, _properties.size, _properties.color);
  item->return_code = return_code;
  item->func = func;
  _items.push_back(item);

  std::vector<TextSP> texts;
  texts.reserve(_items.size());
  for(const auto& item : _items)
    texts.push_back(item->text);

  const auto& bg_pos = _background->getPosition();
  const auto& bounds = getGlobalBounds();
  utils::graphics::vAlign(texts, getPosition().x, getPosition().y + _text_y_offset, bounds.height - _text_y_offset);
  for(auto& text : texts)
  {
    utils::graphics::centerHonrizontally(*text->text(), bounds.width);
    const auto& pos = text->getPosition();
    text->setPosition(bg_pos.x + pos.x, pos.y);
  }
}

}
