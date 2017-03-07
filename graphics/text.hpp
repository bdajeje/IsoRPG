#ifndef TEXT_HPP
#define TEXT_HPP

#include <memory>
#include <SFML/Graphics/Text.hpp>
#include "graphics/drawable.hpp"

namespace graphics {

struct TextProperties
{
  TextProperties(sf::Color color, std::string font, int size)
    : color {color}
    , font {font}
    , size {size}
  {}

  sf::Color color;
  std::string font;
  int size;
};

class Text final : public Drawable
{
  public:

    Text(const sf::String& string, const sf::Font& font, unsigned int characterSize = 30, const sf::Color& color = sf::Color::Black);

    const sf::String& getString() const { return _text->getString(); }
    sf::FloatRect getGlobalBounds() const { return _text->getGlobalBounds(); }
    sf::FloatRect getLocalBounds() const { return _text->getLocalBounds(); }
    virtual const sf::Color getColor() const override { return _text->getColor(); }
    std::shared_ptr<sf::Text> text() noexcept { return _text; }

    void setString(const sf::String& string) { _text->setString(string); }
    virtual void setColor(const sf::Color& color) override { _text->setColor(color); }
    void setCharacterSize(unsigned int size) { _text->setCharacterSize(size); }
    void setFont(const sf::Font& font) { _text->setFont(font); }

  protected:

    void internalDraw(sf::RenderTarget& target, sf::RenderStates states) const noexcept override;

  private:

    std::shared_ptr<sf::Text> _text;
};

using TextSP = std::shared_ptr<Text>;

TextSP getText(const sf::Font& font, const std::string& text_content, uint character_size, const sf::Color& color);
TextSP getText(const std::string& font_name, const std::string& text_content, uint character_size, const sf::Color& color);

}

#endif // TEXT_HPP
