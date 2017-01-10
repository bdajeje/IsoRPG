#ifndef BOUNCINGSPRITE_HPP
#define BOUNCINGSPRITE_HPP

#include <SFML/Graphics.hpp>
#include "graphics/animations/sprite_animation.hpp"

namespace graphics {
namespace animations {

class BouncingSprite final : public SpriteAnimation
{
  public:

    BouncingSprite(std::shared_ptr<Sprite>& sprite, float x_bounce, float y_bounce, const sf::Time& time);

    virtual void update(const sf::Time& elapsed_time) override;

  private:

    float _x_bounce;
    float _y_bounce;
    const int _time;
    const sf::Vector2f _original_pos;
    int _elapsed_time {0};
    bool _forward {true}; // To manage bouncing direction
};

using BouncingSpriteSP = std::shared_ptr<BouncingSprite>;

}
}

#endif // BOUNCINGSPRITE_HPP
