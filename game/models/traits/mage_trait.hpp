#ifndef MAGETRAIT_HPP
#define MAGETRAIT_HPP

#include "game/models/character_trait.hpp"

namespace game {

class MageTrait : public CharacterTrait
{
  public:

    static constexpr char* Name {"Mage"};

    MageTrait();
};

}

#endif // MAGETRAIT_HPP
