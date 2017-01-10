#ifndef WARRIORTRAIT_HPP
#define WARRIORTRAIT_HPP

#include "game/models/character_trait.hpp"

namespace game {

class WarriorTrait : public CharacterTrait
{
  public:

    static constexpr char* Name {"Warrior"};

    WarriorTrait();
};

}

#endif // WARRIORTRAIT_HPP
