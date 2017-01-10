#include <iostream>
#include <memory>

#include <SFML/Graphics.hpp>

#include "managers/font_manager.hpp"
#include "managers/sound_manager.hpp"
#include "managers/music_manager.hpp"
#include "managers/texture_manager.hpp"
#include "managers/window.hpp"
#include "utils/settings.hpp"
#include "utils/exception.hpp"
#include "utils/directory.hpp"
#include "game/game.hpp"

int main(int /*argc*/, char **argv)
{
  const std::string current_dir = utils::dir(argv[0]);

  try
  {
    // Read settings
    utils::Settings::init(current_dir + "/resources/settings");

    // Set anti aliasing
    sf::ContextSettings context;
//    context.antialiasingLevel = 8;

    // Create window
    std::unique_ptr<mgr::Window>& window = mgr::Window::init("Star Wars...", sf::Style::Default, context);
    window->setFramerateLimit(60);

    // Init managers
    font::FontManager::init(current_dir + "/resources/fonts/");
    sound::SoundManager::init(current_dir + "/resources/sounds/");
    manager::MusicManager::init(current_dir + "/resources/musics/");
    texture::TextureManager::init(current_dir + "/resources/sprites/");

    // Init random
    srand(time(NULL));

    // Game loop
    game::GameSP game = game::Game::init();
    game->start();
  }
  catch(const utils::Exception& e)
  {
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
