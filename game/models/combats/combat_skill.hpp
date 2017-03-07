#ifndef COMBATSKILL_HPP
#define COMBATSKILL_HPP

#include <memory>

#include "game/models/character_skill.hpp"
#include "game/models/combats/skill_area.hpp"

namespace game {

class CombatSkill : public CharacterSkill
{
  public:

    CombatSkill(const json& data);
    virtual ~CombatSkill() = default;

    short energyCost() const noexcept { return _energy_cost; }
    const SkillAreaSP& area() const noexcept { return _area; }

  protected:

    SkillAreaSP _area;
    short _energy_cost;
};

using CombatSkillSP = std::shared_ptr<CombatSkill>;

}

#endif // COMBATSKILL_HPP
