#include "helmet_item.hpp"

namespace game {

HelmetItem::HelmetItem(const json& data)
  : PortableItem(data)
{
  _protection = data["stats"]["protection"];
}

json HelmetItem::save()
{
  auto data = PortableItem::save();

  data["stats"]["protection"] = _protection;

  return data;
}

}
