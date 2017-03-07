#include "character_skill.hpp"

namespace game {

CharacterSkill::CharacterSkill(const json& data)
{
  std::string icon = data["icon"];
  _icon = icon;
}

}
