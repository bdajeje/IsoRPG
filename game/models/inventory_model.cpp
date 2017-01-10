#include "inventory_model.hpp"

namespace game {

InventoryModel::InventoryModel(const json& data)
{
  _width  = data["inventory"]["max_width"];
  _height = data["inventory"]["max_height"];

  const auto& inventory_items = data["inventory"]["items"];
  _inventory_items.reserve(inventory_items.size());
  for(const auto& item_data : inventory_items)
    _inventory_items.push_back(PortableItem::create(item_data));
}

json InventoryModel::save()
{
  json data;

  data["inventory"]["max_height"] = _height;
  data["inventory"]["max_width"] = _width;
  for(const auto& item : _inventory_items)
    data["inventory"]["items"].push_back(item->save());

  return data;
}

}
