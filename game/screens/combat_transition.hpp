#ifndef COMBATTRANSITION_HPP
#define COMBATTRANSITION_HPP

#include "game/interactible_screen.hpp"
#include "graphics/sprite.hpp"
#include "graphics/animation.hpp"

namespace game {
namespace screen {

class CombatTransition final : public InteractibleScreen
{
  public:

    enum class Transition { CornersExit, HorizontalSplit, VerticalSplit };

    CombatTransition();

    virtual events::EventAction handleEvents(const sf::Event& event) override;
    virtual void update(const sf::Time& elapsed_time) override;

  private:

    void create(Transition);
    std::vector<graphics::SpriteSP> prepareSprites(size_t nbr_parts);

  private:

    sf::Texture _texture;
    graphics::AnimationSP _animation;
    sf::Time _animation_time;
};

}
}

#endif // COMBATTRANSITION_HPP
