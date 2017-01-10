#ifndef TREASURESCREEN_HPP
#define TREASURESCREEN_HPP

#include "game/interactible_screen.hpp"
#include "game/models/characters_team.hpp"
#include "graphics/inventory.hpp"
#include "graphics/inventory.hpp"
#include "utils/json.hpp"
#include "game/interactions/treasure_interaction.hpp"

namespace game {
namespace screen {

class TreasureScreen final : public InteractibleScreen
{
  public:

    TreasureScreen(TreasureInteractionSP interaction);
    ~TreasureScreen();

    events::EventAction handleEvents(const sf::Event& event) override;

  private:

    std::map<CharacterSP, graphics::InventorySP> _inventories;
    graphics::InventorySP _treasure_inventory;
    TreasureInteractionSP _interaction;
};

}
}

#endif // TREASURESCREEN_HPP
