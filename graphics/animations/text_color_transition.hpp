#ifndef TEXTCOLORTRANSITION_HPP
#define TEXTCOLORTRANSITION_HPP

#include "graphics/animations/text_animation.hpp"

namespace graphics {
namespace animations {

class TextColorTransition final : public TextAnimation
{
  public:

    TextColorTransition(TextSP& text, const sf::Color& target, const sf::Time& time);

    virtual void update(const sf::Time& elapsed_time) override;

  private:

    const sf::Color _original;
    const sf::Color _target;
    int _time;
    int _elapsed_time {0};
};

}
}

#endif // TEXTCOLORTRANSITION_HPP
