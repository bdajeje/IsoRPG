#ifndef ENNEMYCHARACTER_HPP
#define ENNEMYCHARACTER_HPP

#include "game/models/character.hpp"

namespace game {

class EnnemyCharacter final : public Character
{
  public:

    EnnemyCharacter(const json& data);
};

using EnnemyCharacterSP = std::shared_ptr<EnnemyCharacter>;

}

#endif // ENNEMYCHARACTER_HPP
