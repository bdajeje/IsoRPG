#include "basic_attack_skill.hpp"

namespace game {

BasicAttackSkill::BasicAttackSkill()
  : CombatSkill {R"(
                 {
                   "icon": "combats/icons/basic_sword.png",
                   "energy_cost": 2,
                   "area": {
                     "type": "cross",
                     "height": 3,
                     "width": 3,
                     "range": 0
                   }
                 }
               )"_json}
{

}

}
