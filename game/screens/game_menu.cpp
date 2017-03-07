#include "game_menu.hpp"

#include "managers/window.hpp"
#include "graphics/models/rectangle.hpp"
#include "game/game.hpp"

namespace game {
namespace screen {

constexpr int MENU_WIDTH = 400;
constexpr int MENU_HEIGHT = 600;

GameMenu::GameMenu()
{
  const unsigned int window_width  = mgr::Window::width();
  const unsigned int window_height = mgr::Window::height();

  graphics::RectangleSP shadow_background = std::make_shared<graphics::Rectangle>();
  shadow_background->shape()->setFillColor(sf::Color{0, 0, 0, 150});
  shadow_background->shape()->setSize(sf::Vector2f{window_width, window_height});
  addDrawable(shadow_background);

  _menu = std::make_shared<graphics::Menu>(MENU_WIDTH, MENU_HEIGHT, 150, graphics::TextProperties{sf::Color::White, "conversation.ttf", 20}, "ui/game_menu.png");
  _menu->setPosition((window_width - MENU_WIDTH) / 2, (window_height - MENU_HEIGHT) / 2);
  _menu->addItem("Resume", events::EventAction::ExitScreen, [](){});
  _menu->addItem("Save", events::EventAction::ExitScreen, [](){});
  _menu->addItem("Load", events::EventAction::ExitScreen, [](){});
  _menu->addItem("Options", events::EventAction::ExitScreen, [](){});
  _menu->addItem("Quit", events::EventAction::ExitScreen, [](){ mgr::Window::instance()->close(); });
  addDrawable(_menu);
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
	  if(isKeyAllowed(sf::Keyboard::S))
		Game::save("1.json");
	  else if(isKeyAllowed(utils::KeyBinding::key(KeyAction::ExitScreen)))
		return events::EventAction::ExitScreen;
	}
  }
#pragma GCC diagnostic pop

  return events::EventAction::Stop;
}

}
}
