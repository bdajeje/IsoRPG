#include "playable_character.hpp"

namespace game {

PlayableCharacter::PlayableCharacter(const json& data)
  : Character(data)
{
   _exp = MaxedValue<uint>(data["exp"]["current"], data["exp"]["max"]);
  _standing_texture_name = data["sprites"]["standing"];
  _start_movement_range  = data["start_movement_range"];
}

json PlayableCharacter::save()
{
  auto data = Character::save();

  data["sprites"]["standing"] = _standing_texture_name;
  data["exp"]["current"] = _exp._value;
  data["exp"]["max"] = _exp._max;

  return data;
}

}
