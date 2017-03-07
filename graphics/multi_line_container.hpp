#ifndef MULTILINECONTAINER_HPP
#define MULTILINECONTAINER_HPP

#include <vector>
#include "managers/font_manager.hpp"
#include "graphics/animations/text_appearance.hpp"

namespace graphics {

class MultiLineContainer : public Drawable
{
  public:

    MultiLineContainer(const std::string& font_name, uint character_size, const sf::Color& color, const sf::FloatRect& bounds, float padding = 5);
    virtual ~MultiLineContainer() = default;

    virtual sf::FloatRect getGlobalBounds() const override;

    bool next() noexcept;
    bool hasNext() const noexcept;
    void finishAnimation() noexcept;

    /*! Are all texts complety shown - animation done */
    bool isAllShown() const noexcept;

    /*! Is current text complety shown - animation done */
    bool isCurrentShown() const noexcept;

    virtual void update(const sf::Time& elapsed_time);

    void setPosition(float x, float y) { _position.x = x; _position.y = y; }
    const sf::Vector2f& getPosition() const noexcept { return _position; }
    void setString(const std::string& text);

    virtual void setColor(const sf::Color& /*color*/) override {}
    virtual const sf::Color getColor() const override { return {}; }

  protected:

    virtual void internalDraw(sf::RenderTarget& target, sf::RenderStates states) const noexcept override;

  private:

    std::vector<TextSP>& current() { return _texts[_current_text]; }
    const std::vector<TextSP>& current() const { return _texts[_current_text]; }
    TextSP addNewLine();
    float currentTextHeight() const;
    void updatePosition(float x, float y);
    void setTextAppearance(TextSP& text);

  private:

    std::vector<std::vector<TextSP>> _texts;
    size_t _current_text {0};
    const sf::Font& _font;
    sf::Color _color;
    uint _character_size;
    sf::FloatRect _bounds;
    sf::Vector2f _position;
    float _line_padding;
    animations::TextAppearanceSP _text_appearance;
};

using MultiLineContainerSP = std::shared_ptr<MultiLineContainer>;

}

#endif // MULTILINECONTAINER_HPP
