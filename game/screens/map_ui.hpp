#ifndef MAPUI_HPP
#define MAPUI_HPP

#include "graphics/text.hpp"
#include "game/interactible_screen.hpp"
#include "game/screens/equipment_screen.hpp"
#include "utils/json.hpp"

namespace game {
namespace screen {

class MapUI final : public InteractibleScreen
{
  public:

    MapUI(const std::string& id, const json& data);

    virtual void update(const sf::Time&elapsed_time) override;
    virtual events::EventAction handleEvents(const sf::Event& event) override;

    std::string mapName() const { return _map_name->getString().toAnsiString(); }
    const std::string& mapID() const { return _id; }

  private:

    void showEquipment() const noexcept;
    void showSkills() const noexcept;
    void showTeam() const noexcept;

  private:

    std::string _id;
    graphics::TextSP _map_name;
    EquipmentScreenSP _equipment_page;
    utils::KeyLimitor _limitor;
};

}
}

#endif // MAPUI_HPP
