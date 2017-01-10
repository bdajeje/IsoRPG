#ifndef COMBATMODEL_HPP
#define COMBATMODEL_HPP

#include "utils/json.hpp"
#include "game/models/ennemy_character.hpp"

namespace game {

class CombatModel
{
  public:

    enum class Mode {
      Placing,
      Fight
    };

    CombatModel(const json& data);

    std::list<EnnemyCharacterSP>& ennemies() { return _ennemies; }
    void addEnnemy(const json& data);

  private:

    std::list<EnnemyCharacterSP> _ennemies;
    Mode _current_mode {Mode::Placing};
};

using CombatModelSP = std::shared_ptr<CombatModel>;

}

#endif // COMBATMODEL_HPP
