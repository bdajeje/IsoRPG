#ifndef TEXTANIMATION_HPP
#define TEXTANIMATION_HPP

#include "graphics/animation.hpp"
#include "managers/font_manager.hpp"

namespace graphics {
namespace animations {

class TextAnimation : public Animation
{
  public:

    TextAnimation(TextSP& text);

    virtual void update(const sf::Time& elapsed_time) override = 0;

    const TextSP& text() const noexcept { return _text; }

  protected:

    TextSP _text;
};

}
}

#endif // TEXTANIMATION_HPP
