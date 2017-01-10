#ifndef PRIESTTRAIT_HPP
#define PRIESTTRAIT_HPP

#include "game/models/character_trait.hpp"

namespace game {

class PriestTrait : public CharacterTrait
{
  public:

    static constexpr char* Name {"Priest"};

    PriestTrait();
};

}

#endif // PRIESTTRAIT_HPP
