#ifndef COMBATUI_HPP
#define COMBATUI_HPP

#include "game/interactible_screen.hpp"
#include "game/models/combat_model.hpp"
#include "game/models/playable_character.hpp"
#include "graphics/models/tileslayout.hpp"
#include "graphics/models/combat_time_line.hpp"
#include "graphics/text.hpp"
#include "graphics/models/button.hpp"
#include "graphics/models/rectangle.hpp"
#include "graphics/models/combat_character_panel.hpp"
#include "graphics/models/combat_player_panel.hpp"

namespace game {
namespace screen {

class CombatUI final : public InteractibleScreen
{
  public:

    CombatUI(CombatModelSP model, graphics::TilesLayoutSP tiles_layout);

    virtual events::EventAction handleEvents(const sf::Event& event) override;
    virtual void update(const sf::Time& elapsed_time) override;

  private:

    void nextCharacterToPlace();
    void startFight();
    events::EventAction handlePlacementEvents(const sf::Event& event);
    events::EventAction handleCombatEvents(const sf::Event& event);
    void focusCharacter(int x, int y, bool stay_focused);
    CharacterSP characterAtMousePos(int x, int y);

  private:

    CombatModelSP _model;   
    graphics::RectangleSP _shadow_background;
    graphics::CombatTimeLineSP _timeline;
    graphics::TextSP _mode_txt;
    std::list<PlayableCharacterSP> _characters_to_place;
    PlayableCharacterSP _character_to_place;
    MapPos _starting_map_pos;
    MapPos _previous_hovered_pos;
    graphics::ButtonSP _start_button;
    graphics::CombatPlayerPanelSP _character_screen;
    graphics::CombatCharacterPanelSP _ennemy_panel;    
    graphics::TilesLayoutSP _tiles_layout;
};

}
}

#endif // COMBATUI_HPP
