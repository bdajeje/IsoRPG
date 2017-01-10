#ifndef DELAY_HPP
#define DELAY_HPP

#include <SFML/System/Time.hpp>

#include "graphics/animation.hpp"

namespace graphics {
namespace animations {

class Delay final : public Animation
{
  public:

    Delay(AnimationSP animation, const sf::Time& delay);

    virtual void update(const sf::Time& time) override;

  private:

    AnimationSP _animation;
    sf::Time _delay;
};

}
}

#endif // DELAY_HPP
