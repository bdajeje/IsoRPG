#ifndef WELCOMESCREEN_H
#define WELCOMESCREEN_H

#include "game/interactible_screen.hpp"

namespace game {
namespace screen {

class WelcomeScreen final : public InteractibleScreen
{
  public:

    WelcomeScreen();

    events::EventAction handleEvents(const sf::Event& event) override;

  private:

    void showScreen(InteractibleScreenSP screen);

  private:

    graphics::ScreenSP _shown_screen;
};

}
}

#endif // WELCOMESCREEN_H
