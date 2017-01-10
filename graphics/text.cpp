#include "text.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include "managers/font_manager.hpp"

namespace graphics {

Text::Text(const sf::String& string, const sf::Font& font, unsigned int characterSize, const sf::Color& color)
  : _text(std::make_shared<sf::Text>(string, font, characterSize))
{
  _text->setColor(color);
  _transformable = _text;
}

void Text::internalDraw(sf::RenderTarget& target, sf::RenderStates states) const noexcept
{
  target.draw(*_text, states);
}

TextSP getText(const sf::Font& font, const std::string& text_content, uint character_size, const sf::Color& color)
{
  auto text = std::make_shared<Text>(text_content, font, character_size);
  text->setColor(color);
  return text;
}

TextSP getText(const std::string& font_name, const std::string& text_content, uint character_size, const sf::Color& color)
{
  return getText(font::FontManager::get(font_name), text_content, character_size, color);
}

}
