#include "defend_skill.hpp"

namespace game {

DefendSkill::DefendSkill()
  : CombatSkill {R"(
                 {
                   "icon": "combats/icons/defend.png",
                   "energy_cost": 3,
                   "area": {
                     "type": "point",
                     "height": 1,
                     "width": 1,
                     "center_range": 0
                   }
                 }
               )"_json}
{

}

}
