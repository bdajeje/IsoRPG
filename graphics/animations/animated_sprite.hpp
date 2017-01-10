#ifndef ANIMATED_SPRITE_HPP
#define ANIMATED_SPRITE_HPP

#include <memory>

#include <SFML/Graphics/Texture.hpp>

#include "graphics/animations/sprite_animation.hpp"

namespace graphics {
namespace animations {

class AnimatedSprite final : public SpriteAnimation
{
  public:

    AnimatedSprite(std::shared_ptr<Sprite>& sprite, const json& data);

    virtual void update(const sf::Time& time) override;
    unsigned int animationTime() const noexcept { return _nbr_elements * _refresh_rate_ms; }

    void setFrameRate(uint value) { _refresh_rate_ms = value; }
    size_t steps() const noexcept { return _nbr_elements; }

    void restart();

  private:

    void updateSprite();

  private:

    size_t _nbr_elements;
    std::string _texture_file;
    unsigned int _refresh_rate_ms;
    unsigned int _total_width;
    unsigned int _elapsed_time {0};
    bool _repeat;
};

using AnimatedSpriteSP = std::shared_ptr<AnimatedSprite>;

}
}

#endif // ANIMATED_SPRITE_HPP
