#ifndef MOVE_HPP
#define MOVE_HPP

#include "graphics/animations/sprite_animation.hpp"
#include "graphics/sprite.hpp"

namespace graphics {
namespace animations {

class Move final : public SpriteAnimation
{
  public:

    Move(SpriteSP sprite, float x, float y, sf::Time time);

    virtual void update(const sf::Time& elapsed_time);

  private:

    float _x_per_ms;
    float _y_per_ms;
    int _time;
    int _elapsed_time {0};
};

}
}

#endif // MOVE_HPP
