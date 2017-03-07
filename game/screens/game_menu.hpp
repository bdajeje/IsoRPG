#ifndef GAMEMENU_HPP
#define GAMEMENU_HPP

#include "game/interactible_screen.hpp"
#include "graphics/models/menu.hpp"

namespace game {
namespace screen {

class GameMenu final : public InteractibleScreen
{
  public:

    GameMenu();

    events::EventAction handleEvents(const sf::Event& event) override;
    virtual void update(const sf::Time& elapsed_time) override;

  private:

    graphics::MenuSP _menu;
};

}
}

#endif // GAMEMENU_HPP
