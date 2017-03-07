#include "game.hpp"
#include "managers/window.hpp"
#include "utils/timer.hpp"
#include "utils/file.hpp"
#include "utils/directory.hpp"
#include "utils/keybinding.h"
#include "utils/json.hpp"
#include "game/screens/welcome_screen.hpp"
#include "game/models/characters_team.hpp"
#include "graphics/mouse.hpp"

namespace game {

namespace {
  bool isScreenFinished(const InteractibleScreenSP& screen)
  {
	return screen->isFinished();
  }
}

std::shared_ptr<Game> Game::_instance;

std::shared_ptr<Game> Game::init()
{
  _instance.reset(new Game);
  return _instance;
}

Game::Game()
{
  _screens.reserve(4);
}

void Game::start()
{
  utils::KeyLimitor::init(100);
  utils::KeyBinding::init(json::parse(utils::files::read("./resources/keybindings.json")));
  graphics::Mouse::init();  

  _screens.push_back(std::make_shared<screen::WelcomeScreen>());
//  loadGame("nani"); // tmp to dev - to remove

  static const sf::Color background_color {0, 0, 0};
  utils::time::Timer timer;

  auto& window = mgr::Window::instance();

  while(window->isOpen())
  {
    const sf::Time elapsed_time {timer.restart()};

    // Handle SFML events
    sf::Event event;
    while(window->pollEvent(event))
    {
      // Close program
      if( event.type == sf::Event::Closed )
      return;

      // Update mouse sprite cursor
      if(event.type == sf::Event::MouseMoved)
      graphics::Mouse::updatePos(event.mouseMove.x, event.mouseMove.y);

      // Prevent screens event if there is a blocking animation
      if(!_blocking_animation)
      handleScreensEvent(event);
    }

    // Handle blocking animation
    if(_blocking_animation && _blocking_animation->isFinished())
    {
      _blocking_animation_handler();
      _blocking_animation.reset();
    }

    // Execute pending interactions
    while(InteractionSP interaction = Interaction::pop())
      interaction->exec();

    // Update screens
    for(size_t i = 0, end = _screens.size(); i < end; ++i)
      _screens[i]->update(elapsed_time);

    // Remove finished screens (don't check map and map UI screens)
    _screens.erase(std::remove_if(_screens.begin() + 2, _screens.end(), isScreenFinished), _screens.end());

    // Draw
    window->clear(background_color);
    for(const auto& screen : _screens)
      window->draw(*screen);
    window->draw(*graphics::Mouse::instance());
    window->display();
  }
}

void Game::show(InteractibleScreenSP screen)
{
  if(screen && _instance->_screens.back() != screen)
  {
	screen->show();
	_instance->_screens.push_back(screen);
  }
}

void Game::handleScreensEvent(const sf::Event& event)
{
  for(size_t i = _screens.size(); i > 0; --i)
  {
	InteractibleScreenSP& screen = _screens[i-1];
	const events::EventAction event_action = screen->handleEvents(event);
	switch(event_action)
	{
	  case events::EventAction::Continue: break;
	  case events::EventAction::ExitScreen:
	  {
		_screens.erase(std::find(_screens.begin(), _screens.end(), screen));
		return;
	  }
	  case events::EventAction::Stop: break;
	  case events::EventAction::Exit: return;
	}

	if(event_action == events::EventAction::Stop)
	  break;
  }
}

void Game::waitForAnimation(const graphics::AnimationSP& animation, std::function<void()> handler)
{
  _instance->_blocking_animation = animation;
  _instance->_blocking_animation_handler = handler;
}

void Game::changeMap(const std::string& map_id)
{
  // Let's asume screen 0 is always the map and screen 1 the map UI
  const json map_data = json::parse(utils::files::read("./resources/maps/"+map_id+"/data.json"));
  _instance->_screens[0] = std::make_shared<screen::Map>(map_data);
  _instance->_screens[1] = std::make_shared<screen::MapUI>(map_id, map_data);
}

void Game::save(std::string directory)
{
  directory = "./resources/saves/" + utils::ensureDirectoryEnd(directory);
  utils::mkdir(directory);

  const std::string maps_dir = directory + "maps/";
  utils::mkdir(maps_dir);

  const std::string map_dir = maps_dir + _instance->_map_UI_screen->mapID();
  utils::mkdir(map_dir);
  utils::files::create(map_dir + "/data.json", _instance->_map_screen->save().dump());

  utils::files::create(directory + "character_team.json", CharactersTeam::instance()->save().dump());

  const std::string characters_dir = directory + "characters/";
  utils::mkdir(characters_dir);
  for(const auto& character : CharactersTeam::instance()->characters())
	utils::files::create(characters_dir + character->name() + ".json", character->save().dump());
}

void Game::hideMapUI()
{
  _instance->_map_UI_screen->hide();
}

void Game::loadGame(const std::string& save_name)
{
  CharactersTeam::init(save_name);

  const std::string map_id {"1"};
	const json map_data = json::parse(utils::files::read("./resources/maps/" + map_id + "/data.json"));
  _instance->_map_screen = std::make_shared<screen::Map>(map_data);
  _instance->_map_UI_screen = std::make_shared<screen::MapUI>(map_id, map_data);

  _instance->_screens.clear();
  _instance->_screens.push_back( _instance->_map_screen );
  _instance->_screens.push_back( _instance->_map_UI_screen );
}

void Game::pop()
{
  _instance->_screens.resize(_instance->_screens.size() - 1);
}

}
