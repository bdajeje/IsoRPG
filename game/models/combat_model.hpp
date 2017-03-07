#ifndef COMBATMODEL_HPP
#define COMBATMODEL_HPP

#include "utils/json.hpp"
#include "game/models/ennemy_character.hpp"
#include "game/models/combats/combat_skill.hpp"

namespace game {

class CombatModel final
{
  public:

    enum class Mode {
      Placement, Combat, CharacterMoving
    };

    enum class Event {
      CharacterTurn
    };

    CombatModel(const json& data);

    void addEnnemy(const json& data);
    void startFight();
    void setMode(Mode mode) { _current_mode = mode; }
    void setSelectedSkill(CombatSkillSP skill) { _selected_skill = skill; }

    CharacterSP currentCharacter() { return _characters.front(); }
    Mode currentMode() const noexcept { return _current_mode; }
    std::list<EnnemyCharacterSP>& ennemies() noexcept { return _ennemies; }
    std::list<game::CharacterSP>& characters() noexcept { return _characters; }
    const CombatSkillSP& selectedSkill() const noexcept { return _selected_skill; }
    void unselectSkill() noexcept { _selected_skill.reset(); }

    void registerEvent(Event event, std::function<void()> func) { _event_registrations[event].push_back(func); }

  private:

    void triggerEvent(Event event);

  private:

    std::list<game::CharacterSP> _characters;
    std::list<EnnemyCharacterSP> _ennemies;
    Mode _current_mode {Mode::Placement};
    CombatSkillSP _selected_skill;
    std::map<Event, std::list<std::function<void()>>> _event_registrations;
};

using CombatModelSP = std::shared_ptr<CombatModel>;

}

#endif // COMBATMODEL_HPP
