#ifndef SPRITE_ANIMATION_HPP
#define SPRITE_ANIMATION_HPP

#include "graphics/animation.hpp"

namespace graphics {

class Sprite;

namespace animations {

class SpriteAnimation : public Animation
{
  public:

    SpriteAnimation(std::shared_ptr<Sprite>& sprite);

    virtual void update(const sf::Time& time) override = 0;

  protected:

    std::shared_ptr<Sprite> _sprite;
};

}
}

#endif // SPRITE_ANIMATION_HPP
