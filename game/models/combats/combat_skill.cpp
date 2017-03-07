#include "combat_skill.hpp"

namespace game {

CombatSkill::CombatSkill(const json& data)
  : CharacterSkill{data}
{
  _area = SkillArea::create(data["area"]);
  _energy_cost = data["energy_cost"];
}

}
