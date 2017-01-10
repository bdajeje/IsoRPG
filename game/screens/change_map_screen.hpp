#ifndef CHANGEMAPSCREEN_HPP
#define CHANGEMAPSCREEN_HPP

#include "game/interactible_screen.hpp"
#include "graphics/models/rectangle.hpp"
#include "graphics/animations/fill_color.hpp"
#include "utils/json.hpp"

namespace game {
namespace screen {

class ChangeMapScreen final : public InteractibleScreen
{
  public:

    ChangeMapScreen(const json& data);

    virtual void update(const sf::Time& elapsed_time) override;

  private:

    json _data;
    graphics::RectangleSP _background;
    graphics::AnimationSP _animation;
    short _step {1};
};

}
}

#endif // CHANGEMAPSCREEN_HPP
