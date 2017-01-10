#ifndef GAMEMENU_HPP
#define GAMEMENU_HPP

#include "game/interactible_screen.hpp"

namespace game {
namespace screen {

class GameMenu final : public InteractibleScreen
{
  public:

    GameMenu();

    events::EventAction handleEvents(const sf::Event& event) override;
    virtual void update(const sf::Time& elapsed_time) override;

  private:

    utils::KeyLimitor _limitor;
};

}
}

#endif // GAMEMENU_HPP
