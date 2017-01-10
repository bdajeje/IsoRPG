#ifndef INVENTORY_MODEL_HPP
#define INVENTORY_MODEL_HPP

#include "game/models/portable_item.hpp"
#include "utils/serializable.hpp"

namespace game {

class InventoryModel final : utils::Serializable
{
  public:

    InventoryModel(const json& data);

    json save();

    size_t width() const noexcept { return _width; }
    size_t height() const noexcept { return _height; }
    std::vector<game::PortableItemSP>& items() { return _inventory_items; }

    void setItems(const std::vector<game::PortableItemSP>& items) { _inventory_items = items; }

  private:

    size_t _width;
    size_t _height;
    std::vector<game::PortableItemSP> _inventory_items;
};

using InventoryModelSP = std::shared_ptr<InventoryModel>;

}

#endif // INVENTORY_MODEL_HPP
