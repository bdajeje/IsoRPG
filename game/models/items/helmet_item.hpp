#ifndef HELMETITEM_HPP
#define HELMETITEM_HPP

#include "game/models/portable_item.hpp"

namespace game {

class HelmetItem final : public PortableItem
{
  public:

    HelmetItem(const json& data);

    virtual json save() override;

  private:

    uint _protection;
};

}

#endif // HELMETITEM_HPP
