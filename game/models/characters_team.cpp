#include "characters_team.hpp"
#include "utils/json.hpp"
#include "utils/file.hpp"

namespace game {

std::shared_ptr<CharactersTeam> CharactersTeam::_instance;

void CharactersTeam::init()
{
  _instance.reset(new CharactersTeam);
}

CharactersTeam::CharactersTeam()
{
  _characters.push_back(std::make_shared<PlayableCharacter>(
                          json::parse(utils::files::read("./resources/progression/jade.json"))));
  _characters.push_back(std::make_shared<PlayableCharacter>(
                          json::parse(utils::files::read("./resources/progression/jeje.json"))));
  _characters.push_back(std::make_shared<PlayableCharacter>(
                          json::parse(utils::files::read("./resources/progression/arthy.json"))));

  _current_map_character = _characters.front();
  _current_map_character->setMapPos(MapPos{10, 18});

  _money = 9923;
}

PlayableCharacterSP CharactersTeam::character(size_t offset) noexcept
{
  if(offset < _instance->_characters.size())
    return _instance->_characters.at(offset);

  return {};
}

json CharactersTeam::save()
{
  json data;

  for(const auto& character : _characters)
    data["characters"].push_back(character->name());

  return data;
}

}
