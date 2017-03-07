#include "characters_team.hpp"
#include "utils/json.hpp"
#include "utils/file.hpp"

namespace game {

std::shared_ptr<CharactersTeam> CharactersTeam::_instance;

void CharactersTeam::init(const std::string& save_name)
{
  _instance.reset(new CharactersTeam(save_name));
}

CharactersTeam::CharactersTeam(const std::string& save_name)
{
  const std::string path = "./resources/saves/" + save_name + "/";
  const json data = json::parse(utils::files::read(path + "character_team.json"));

  for(const std::string& character_name : data["characters"])
  {
    _characters.push_back(std::make_shared<PlayableCharacter>(
                            json::parse(utils::files::read(path + "characters/" + character_name + ".json"))));
  }

  _current_map_character = _characters.front();
  _current_map_character->setMapPos(MapPos{data["map"]["pos"][0], data["map"]["pos"][1]});

  _money = data["money"];
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

  data["money"] = _money;
  data["map"]["name"] = "todo";
  data["map"]["pos"][0] = 10; // todo
  data["map"]["pos"][1] = 18; // todo

  return data;
}

}
