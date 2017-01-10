#ifndef MAP_HPP
#define MAP_HPP

#include "graphics/sprite.hpp"
#include "graphics/models/tileslayout.hpp"
#include "game/interactible_screen.hpp"
#include "game/models/combat_model.hpp"
#include "utils/typedefs.hpp"
#include "utils/serializable.hpp"

namespace game {
namespace screen {

struct CombatPhase
{
    CombatPhase(const json& data);

    json _data;
    std::string _music;
};

class Map final : public InteractibleScreen
                , public utils::Serializable
{
  public:

    enum class MapMode { Visit, Combat };

    Map(const json& data);

    virtual void update(const sf::Time&elapsed_time) override;
    virtual events::EventAction handleEvents(const sf::Event& event) override;
    virtual json save() override;

  private:

    void triggerCombatChance();
    void startCombat(const CombatPhase& combat_phase);
    void updateVisit(const sf::Time& elapsed_time);
    void updateCombat(const sf::Time& elapsed_time);
    events::EventAction handleVisitEvents(const sf::Event& event);
    events::EventAction handleCombatEvents(const sf::Event& event);

  private:

    utils::KeyLimitor _limitor;
    std::vector<graphics::SpriteSP> _sprite_layouts;
    graphics::TilesLayoutSP _tiles_layout;
    bool _show_tiles {true};
    graphics::Path _player_path;
    MapMode _current_mode {MapMode::Visit};
    short _combat_probability {0};
    std::vector<CombatPhase> _combats;
    CombatModelSP _combat_model;        
};

}
}

#endif // MAP_HPP
