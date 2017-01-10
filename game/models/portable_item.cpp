#include "portable_item.hpp"
#include "game/models/items/weapon_item.hpp"
#include "game/models/items/helmet_item.hpp"
#include "utils/str.hpp"

#include <iostream>

namespace game {

PortableItemSP PortableItem::create(const json& data)
{
  const std::string& type = data["type"];

  if(type == "weapon")
    return std::make_shared<WeaponItem>(data);
  else if(type == "helmet")
    return std::make_shared<HelmetItem>(data);
  else
    return {};
}

PortableItem::PortableItem(const json& data)
{
  _texture_filename = data["sprites"]["inventory"];
  _pos_in_container = sf::Vector2i{data["pos"][0], data["pos"][1]};
  _inventory_size   = sf::Vector2i{data["size"][0], data["size"][1]};
}

json PortableItem::save()
{
  json data;

  data["pos"][0] = _pos_in_container.x;
  data["pos"][1] = _pos_in_container.y;
  data["size"][0] = _inventory_size.x;
  data["size"][1] = _inventory_size.y;
  data["sprites"]["inventory"] = _texture_filename;

  return data;
}

}
