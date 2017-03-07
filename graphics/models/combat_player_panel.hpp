#ifndef COMBATPLAYERPANEL_HPP
#define COMBATPLAYERPANEL_HPP

#include "graphics/text.hpp"
#include "graphics/models/fill_bar.hpp"
#include "graphics/models/tileslayout.hpp"
#include "game/interactible_screen.hpp"
#include "game/models/playable_character.hpp"
#include "game/models/combat_model.hpp"

namespace graphics {

class CombatPlayerPanel final : public game::InteractibleScreen
{
  public:

    CombatPlayerPanel(const sf::Vector2f& pos, game::CombatModelSP model, TilesLayoutSP& tiles_layout);

    void setPosition(float x, float y);
    void setCharacter(game::PlayableCharacterSP& character);

    virtual game::events::EventAction handleEvents(const sf::Event& event) override;
    virtual void update(const sf::Time& time) override;

  private:

    void updateHealth();
    void updateMana();
    void updateSkills();
    void updateMovements();
    void skillHover(size_t i);
    void skillUnhover(size_t i);
    void skillClicked(size_t i);
    bool handleKeyPressed();

  private:

    game::CombatModelSP _model;
    graphics::TilesLayoutSP _tiles_layout;
    game::PlayableCharacterSP _character;
    SpriteSP _background;
    SpriteSP _face;
    TextSP _health;
    TextSP _mana;
    FillBarSP _health_bar;
    FillBarSP _mana_bar;
    std::vector<SpriteSP> _skills;
    std::vector<TextSP> _skill_shortcuts;
    std::vector<RectangleSP> _energies;
    std::vector<RectangleSP> _skill_highlights;
    std::vector<RectangleSP> _movements;    
    short _remaining_movements {0};

    const sf::Color _energy_default_color;
};

using CombatPlayerPanelSP = std::shared_ptr<CombatPlayerPanel>;

}

#endif // COMBATPLAYERPANEL_HPP
