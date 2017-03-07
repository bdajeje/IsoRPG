#ifndef GAME_HPP
#define GAME_HPP

#include <memory>
#include <list>

#include <SFML/Graphics.hpp>

#include "game/screens/map.hpp"
#include "game/screens/map_ui.hpp"
#include "game/interactible_screen.hpp"
#include "game/interaction.hpp"
#include "graphics/animation.hpp"

namespace game {

class Game
{
  public:

    static std::shared_ptr<Game> init();
    static void show(InteractibleScreenSP screen);
    static void pop();
    static void waitForAnimation(const graphics::AnimationSP& animation, std::function<void()> handler);
    static void changeMap(const std::string& map_id);
    static void save(std::string directory);
    static void hideMapUI();
    static void loadGame(const std::string& filepath);

    void start();

  private:

    Game();
    void handleScreensEvent(const sf::Event& event);

  private:

    std::shared_ptr<screen::Map> _map_screen;
    std::shared_ptr<screen::MapUI> _map_UI_screen;
    std::vector<InteractibleScreenSP> _screens;

    graphics::AnimationSP _blocking_animation;
    std::function<void()> _blocking_animation_handler;

    static std::shared_ptr<Game> _instance;
};

using GameSP = std::shared_ptr<Game>;

}

#endif // GAME_HPP
