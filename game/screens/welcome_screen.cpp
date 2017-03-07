#include "welcome_screen.hpp"

#include "graphics/text.hpp"
#include "graphics/sprite.hpp"
#include "graphics/models/button.hpp"
#include "game/screens/settings_screen.hpp"
#include "game/screens/choose_saved_game_screen.hpp"
#include "managers/window.hpp"
#include "managers/music_manager.hpp"
#include "game/game.hpp"
#include "utils/musics.hpp"

namespace game {
namespace screen {

WelcomeScreen::WelcomeScreen()
{
  const auto window_size = mgr::Window::instance()->getSize();

  auto background = graphics::getSprite("welcome_screen/background.png", window_size.x, window_size.y);
  addDrawable(background);

  const graphics::TextProperties text_props {sf::Color::White, "Breathe_Fire.otf", 30};
  constexpr float buttons_padding {50};

  auto play_button = std::make_shared<graphics::Button>("CONTINUE", text_props);
  play_button->setPosition((window_size.x - play_button->getGlobalBounds().width) / 2, 750);
  addDrawable(play_button);

  const auto play_button_pos = play_button->getPosition();
  const auto play_button_bounds = play_button->getGlobalBounds();

  auto settings_button = std::make_shared<graphics::Button>("SETTINGS", text_props);
  settings_button->setPosition(play_button_pos.x - settings_button->getGlobalBounds().width - buttons_padding, play_button_pos.y);
  addDrawable(settings_button);

  auto load_button = std::make_shared<graphics::Button>("LOAD", text_props);
  load_button->setPosition(play_button_pos.x + play_button_bounds.width + buttons_padding, play_button_pos.y);
  addDrawable(load_button);

  auto quit_button = std::make_shared<graphics::Button>("QUIT", text_props);
  quit_button->setPosition(window_size.x - quit_button->getGlobalBounds().width - buttons_padding, play_button_pos.y);
  addDrawable(quit_button);

  addHoverable(play_button);
  addHoverable(settings_button);
  addHoverable(load_button);
  addHoverable(quit_button);

  addClickable(play_button, []() { Game::loadGame("todo - set which save file to load"); });
  addClickable(settings_button, [=]() { showScreen(std::make_shared<SettingsScreen>()); });
  addClickable(load_button, [=]() { showScreen(std::make_shared<ChooseSavedGameScreen>()); });
  addClickable(quit_button, []() { mgr::Window::instance()->close(); });

  manager::MusicManager::instance().play(musics::WelcomeScreen);
}

events::EventAction WelcomeScreen::handleEvents(const sf::Event& event)
{
  if(InteractibleScreen::handleEvents(event) == events::EventAction::Stop)
    return events::EventAction::Stop;

  return events::EventAction::Stop;
}

void WelcomeScreen::showScreen(InteractibleScreenSP screen)
{
  if(_shown_screen == screen)
    return;

  if(_shown_screen)
    Game::pop();

  _shown_screen = screen;
  Game::show(screen);
}

}
}
