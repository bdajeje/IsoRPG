#include "combat_model.hpp"
#include "game/models/characters_team.hpp"

namespace game {

CombatModel::CombatModel(const json& data)
{
  _characters.insert(_characters.end(), CharactersTeam::instance()->characters().begin(), CharactersTeam::instance()->characters().end());
  for(auto& character : _characters)
    character->startCombat();

  for(const auto& ennemy_data : data[0]["ennemies"])
    addEnnemy(ennemy_data);

  // Order characters
  _characters.sort([](const game::CharacterSP& character_1, const game::CharacterSP& character_2) {
    return character_1->speed() > character_2->speed();
  });
}

void CombatModel::addEnnemy(const json& data)
{
  auto ennemy = std::make_shared<EnnemyCharacter>(data);
  _ennemies.push_back(ennemy);
  _characters.push_back(ennemy);
}

void CombatModel::startFight()
{
  _current_mode = Mode::Combat;
  triggerEvent(Event::CharacterTurn);
}

void CombatModel::triggerEvent(Event event)
{
  auto it = _event_registrations.find(event);
  if(it == _event_registrations.end())
    return;

  for(const auto& registration : it->second)
    registration();
}

}
