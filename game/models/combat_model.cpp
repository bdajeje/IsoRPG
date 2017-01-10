#include "combat_model.hpp"

namespace game {

CombatModel::CombatModel(const json& data)
{
  for(const auto& ennemy_data : data[0]["ennemies"])
    addEnnemy(ennemy_data);
}

void CombatModel::addEnnemy(const json& data)
{
  EnnemyCharacterSP ennemy = std::make_shared<EnnemyCharacter>(data);
  _ennemies.push_back(ennemy);
}

}
