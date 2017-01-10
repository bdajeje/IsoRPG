#ifndef TREASUREINTERACTION_HPP
#define TREASUREINTERACTION_HPP

#include "game/interaction.hpp"
#include "game/models/portable_item.hpp"
#include "game/models/inventory_model.hpp"
#include "graphics/sprite.hpp"

namespace game {

class TreasureInteraction final : public Interaction
                                , public std::enable_shared_from_this<TreasureInteraction>
{
  public:

    TreasureInteraction(const json& data, const graphics::SpriteSP& sprite);

    virtual void exec() override;
    virtual json save() override;

    void setItems(const std::vector<PortableItemSP>& items);

    InventoryModelSP model() const { return _model; }

  private:

    graphics::SpriteSP _sprite;
    InventoryModelSP _model;
    bool _already_executed {false};
    graphics::animations::AnimatedSpriteSP _animation;
};

using TreasureInteractionSP = std::shared_ptr<TreasureInteraction>;

}

#endif // TREASUREINTERACTION_HPP
