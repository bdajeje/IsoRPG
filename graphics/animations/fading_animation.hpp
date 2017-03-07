#ifndef FADING_ANIMATION_HPP
#define FADING_ANIMATION_HPP

#include "graphics/animation.hpp"
#include "graphics/drawable.hpp"

namespace graphics {
namespace animations {

class FadingAnimation final : public Animation
{
  public:

    enum class Type { In, Out };

    FadingAnimation(DrawableSP drawable, const sf::Time& time, Type type, bool start = true);

    virtual void update(const sf::Time& elapsed_time) override;
    void start() noexcept;

  private:

    DrawableSP _drawable;
    const uint _time;
    uint _elapsed_time {0};
    Type _type;
    bool _started;
};

using FadingAnimationSP = std::shared_ptr<FadingAnimation>;

}
}

#endif // FADING_ANIMATION_HPP
