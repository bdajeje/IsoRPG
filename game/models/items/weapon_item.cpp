#include "weapon_item.hpp"

namespace game {

WeaponItem::WeaponItem(const json& data)
  : PortableItem(data)
{
  _strengh = data["stats"]["strengh"];
}

json WeaponItem::save()
{
  auto data = PortableItem::save();

  data["stats"]["strengh"] = _strengh;

  return data;
}

}
