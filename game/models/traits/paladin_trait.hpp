#ifndef PALADINTRAIT_HPP
#define PALADINTRAIT_HPP

#include "game/models/character_trait.hpp"

namespace game {

class PaladinTrait : public CharacterTrait
{
  public:

    static constexpr char* Name {"Paladin"};

    PaladinTrait();
};

}

#endif // PALADINTRAIT_HPP
