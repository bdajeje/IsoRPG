#ifndef WEAPONITEM_HPP
#define WEAPONITEM_HPP

#include "game/models/portable_item.hpp"
#include <SFML/System.hpp>

namespace game {

class WeaponItem final : public PortableItem
{
  public:

    WeaponItem(const json& data);

    virtual json save() override;

  private:

    int _strengh;
};

}

#endif // WEAPONITEM_HPP
