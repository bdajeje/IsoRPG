#ifndef CHOOSESAVEDGAMESCREEN_HPP
#define CHOOSESAVEDGAMESCREEN_HPP

#include <chrono>

#include "game/interactible_screen.hpp"

namespace game {
namespace screen {

struct SavedGameInfo {
  SavedGameInfo(std::string save_name, unsigned int time_played)
    : save_name {save_name}
    , time_played {time_played}
  {}

  std::string save_name;
  unsigned int time_played; // mins
};

class ChooseSavedGameScreen final : public InteractibleScreen
{
  public:

    ChooseSavedGameScreen();

//    events::EventAction handleEvents(const sf::Event& event) override;

  private:

    std::vector<SavedGameInfo> readSavedGames(const std::__cxx11::string& directory) const noexcept;

  private:

    std::vector<SavedGameInfo> _saved_games;
};

}
}

#endif // CHOOSESAVEDGAMESCREEN_HPP
