#include "change_map.hpp"
#include "graphics/mouse.hpp"
#include "game/game.hpp"
#include "game/screens/change_map_screen.hpp"

namespace game {

ChangeMap::ChangeMap(const json& data)
  : Interaction (data, InteractionType::ChangeMap)
{}

void ChangeMap::mouseHover()
{
  graphics::Mouse::setStatus(graphics::Mouse::Status::ChangeMap);
}

void ChangeMap::exec()
{
  const auto& data = _data[0];
  Game::show(std::make_shared<screen::ChangeMapScreen>(data));
}

json ChangeMap::save()
{
  return _data;
}

}
