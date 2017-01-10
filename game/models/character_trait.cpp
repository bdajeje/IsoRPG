#include "character_trait.hpp"
#include "game/models/traits/warrior_trait.hpp"
#include "game/models/traits/paladin_trait.hpp"
#include "game/models/traits/mage_trait.hpp"
#include "game/models/traits/priest_trait.hpp"

namespace game {

CharacterTraitSP CharacterTrait::create(const std::string& name)
{
  if(name == WarriorTrait::Name)
    return std::make_shared<WarriorTrait>();
  else if(name == PaladinTrait::Name)
    return std::make_shared<PaladinTrait>();
  else if(name == MageTrait::Name)
    return std::make_shared<MageTrait>();
  else if(name == PriestTrait::Name)
    return std::make_shared<PriestTrait>();

  return {};
}

CharacterTrait::CharacterTrait(const std::string& name)
  : _name {name}
{

}

}
