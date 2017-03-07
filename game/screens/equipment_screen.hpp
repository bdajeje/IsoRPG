#ifndef EQUIPMENTSCREEN_HPP
#define EQUIPMENTSCREEN_HPP

#include "game/interactible_screen.hpp"
#include "graphics/text.hpp"
#include "graphics/models/rectangle.hpp"
#include <graphics/inventory.hpp>

namespace game {
namespace screen {

class EquipmentScreen final : public InteractibleScreen
{
  public:

    EquipmentScreen();

    virtual void update(const sf::Time& elapsed_time) override;

    virtual events::EventAction handleEvents(const sf::Event& event) override;
    virtual void show() override;

    size_t selectedCharacter() const noexcept;

  private:

    void showPlayer(size_t offset);

  private:

    graphics::TextSP _name_text;
    graphics::TextSP _level_text;
    graphics::TextSP _life_text;
    graphics::TextSP _mana_text;
    graphics::TextSP _traits_text;
    graphics::TextSP _money_text;
    graphics::RectangleSP _exp_bar;
    graphics::SpriteSP _character_standing;
    graphics::InventorySP _inventory;
    std::vector<graphics::SpriteSP> _character_thumbnails;
    std::vector<graphics::SpriteSP> _character_faces;
    size_t _selected_character {std::numeric_limits<size_t>::max()};
};

using EquipmentScreenSP = std::shared_ptr<EquipmentScreen>;

}
}

#endif // EQUIPMENTSCREEN_HPP
