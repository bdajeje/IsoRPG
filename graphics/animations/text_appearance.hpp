#ifndef TEXTAPPEARANCE_HPP
#define TEXTAPPEARANCE_HPP

#include "graphics/animations/text_animation.hpp"
#include "managers/font_manager.hpp"

namespace graphics {
namespace animations {

class TextAppearance final : public TextAnimation
{
  public:

    TextAppearance(TextSP& text, const sf::Time& time);

    virtual void update(const sf::Time& elapsed_time) override;

    void finish() noexcept;

  private:

    const sf::String _original_text;
    int _time;
    int _elapsed_time {0};
};

using TextAppearanceSP = std::shared_ptr<TextAppearance>;

}
}

#endif // TEXTAPPEARANCE_HPP
