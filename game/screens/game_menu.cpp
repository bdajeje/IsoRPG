#include "game_menu.hpp"

#include "managers/window.hpp"
#include "graphics/models/rectangle.hpp"
#include "game/game.hpp"

namespace game {
namespace screen {

GameMenu::GameMenu()
  : _limitor {50}
{
  const unsigned int window_width  = mgr::Window::width();
  const unsigned int window_height = mgr::Window::height();

  graphics::RectangleSP shadow_background = std::make_shared<graphics::Rectangle>();
  shadow_background->shape()->setFillColor(sf::Color{0, 0, 0, 150});
  shadow_background->shape()->setSize(sf::Vector2f{window_width, window_height});
  addDrawable(shadow_background);
}

void GameMenu::update(const sf::Time& elapsed_time)
{
  InteractibleScreen::update(elapsed_time);
}

events::EventAction GameMenu::handleEvents(const sf::Event& event)
{
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wswitch"
  switch(event.type)
  {
    case sf::Event::KeyPressed:
    {
      if(isKeyAllowed(sf::Keyboard::S, _limitor))
        Game::save("1");
      else if(isKeyAllowed(sf::Keyboard::Escape, _limitor))
        return events::EventAction::ExitScreen;
    }
  }
#pragma GCC diagnostic pop

  return events::EventAction::Stop;
}

}
}
