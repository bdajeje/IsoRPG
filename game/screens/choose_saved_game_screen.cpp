#include "choose_saved_game_screen.hpp"
#include "utils/directory.hpp"
#include "utils/file.hpp"
#include "utils/json.hpp"
#include "utils/time.hpp"
#include "utils/str.hpp"
#include "utils/sprites.hpp"
#include "graphics/models/container.hpp"
#include "graphics/text.hpp"
#include "managers/window.hpp"
#include "game/models/characters_team.hpp"

namespace game {
namespace screen {

namespace {
  constexpr int MAIN_CONTAINER_WIDTH = 500;
  constexpr int MAIN_CONTAINER_HEIGHT = 600;
  constexpr int MAIN_CONTAINER_Y_POS = 100;
  constexpr int CONTAINER_WIDTH = 470;
  constexpr int CONTAINER_HEIGHT = 120;
  constexpr int CONTAINER_STARTING_X = 15;
  constexpr int CONTAINER_STARTING_Y = 15;
  constexpr int CONTAINER_Y_PADDING = 5;
  constexpr int SAVE_NAME_X = 10;
  constexpr int SAVE_NAME_Y = 2;
  constexpr int PLAY_TIME_X_OFFSET = 10;
  constexpr int PLAY_TIME_Y = 2;
  constexpr int FACE_WIDTH = 60;
  constexpr int FACE_HEIGHT = 60;
  constexpr int FACE_X_PADDING = 10;
  constexpr int FACE_POS_X = 10;
  constexpr int FACE_POS_Y = 30;
  constexpr int TEXT_SIZE = 20;
  constexpr int LVL_TEXT_SIZE = 15;
  constexpr int LVL_Y_PADDING = 5;
  constexpr int TEXT_Y_PADDING = 5;
  constexpr int MONEY_ICON_WIDTH = 13;
  constexpr int MONEY_ICON_HEIGHT = 11;
  constexpr int MONEY_X_PADDING = 10;
  constexpr int MONEY_Y_PADDING = 10;
}

ChooseSavedGameScreen::ChooseSavedGameScreen()
{
  sf::Vector2f main_container_pos {(mgr::Window::width() - MAIN_CONTAINER_WIDTH) / 2, MAIN_CONTAINER_Y_POS};
  graphics::ContainerSP main_container = std::make_shared<graphics::Container>(MAIN_CONTAINER_WIDTH, MAIN_CONTAINER_HEIGHT, main_container_pos);
  addDrawable(main_container);

  _saved_games = readSavedGames("./resources/saves");

  sf::Vector2f pos {CONTAINER_STARTING_X, CONTAINER_STARTING_Y};
  for(const auto& saved_game : _saved_games)
  {
    graphics::ContainerSP container = std::make_shared<graphics::Container>(CONTAINER_WIDTH, CONTAINER_HEIGHT, pos, graphics::ContainerProps{sf::Color{100, 100, 100}});
    main_container->addDrawable(container, pos);

    graphics::TextSP save_name = graphics::getText("Breathe_Fire.otf", saved_game.save_name, TEXT_SIZE, sf::Color::Black);
    sf::Vector2f save_name_pos {SAVE_NAME_X, SAVE_NAME_Y};

    graphics::TextSP play_time = graphics::getText("Breathe_Fire.otf", utils::readableTime(saved_game.time_played), TEXT_SIZE, sf::Color::Black);
    sf::Vector2f play_time_pos {CONTAINER_WIDTH - PLAY_TIME_X_OFFSET - play_time->getGlobalBounds().width, PLAY_TIME_Y};

    CharactersTeam team = CharactersTeam(saved_game.save_name);

    graphics::TextSP money = graphics::getText("Breathe_Fire.otf", utils::readableMoney(team.money()), TEXT_SIZE, sf::Color::Black);
    sf::Vector2f money_pos {CONTAINER_WIDTH - PLAY_TIME_X_OFFSET - money->getGlobalBounds().width, play_time_pos.y + play_time->getGlobalBounds().height + TEXT_Y_PADDING};

    graphics::SpriteSP money_icon = graphics::getSprite(sprites::MONEY_ICON, MONEY_ICON_WIDTH, MONEY_ICON_HEIGHT);
    sf::Vector2f money_icon_pos {money_pos.x - money_icon->getGlobalBounds().width - MONEY_X_PADDING, money_pos.y + MONEY_Y_PADDING};

    sf::Vector2f face_pos {FACE_POS_X, FACE_POS_Y};
    for(const auto& character : team.characters())
    {
      graphics::SpriteSP face = graphics::getSprite(character->faceTextureName(), FACE_WIDTH, FACE_HEIGHT);
      container->addDrawable(face, face_pos);

      graphics::TextSP level = graphics::getText("Breathe_Fire.otf", "lvl " + std::to_string(character->level()), LVL_TEXT_SIZE, sf::Color::Black);
      container->addDrawable(level, sf::Vector2f{face_pos.x + (FACE_WIDTH - level->getGlobalBounds().width) / 2, face_pos.y + FACE_HEIGHT + LVL_Y_PADDING});

      face_pos.x += FACE_WIDTH + FACE_X_PADDING;
    }

    container->addDrawable(save_name, save_name_pos);
    container->addDrawable(play_time, play_time_pos);
    container->addDrawable(money, money_pos);
    container->addDrawable(money_icon, money_icon_pos);
    pos.y += CONTAINER_HEIGHT + CONTAINER_Y_PADDING;
  }
}

//events::EventAction ChooseSavedGameScreen::handleEvents(const sf::Event& event)
//{

//}

std::vector<SavedGameInfo> ChooseSavedGameScreen::readSavedGames(const std::string& directory) const noexcept
{
  std::vector<std::string> saves_dirs = utils::listDirs(directory, ".*");
  std::vector<SavedGameInfo> results;
  results.reserve(saves_dirs.size());

  const std::string dir = utils::ensureDirectoryEnd(directory);

  for(const std::string& save_dir : saves_dirs)
  {
    const json info = json::parse(utils::files::read(dir + utils::ensureDirectoryEnd(save_dir) + "info.json"));
    results.emplace_back( save_dir, static_cast<unsigned int>(info["saved_game"]["time_play"]) );
  }

  return results;
}

}
}
