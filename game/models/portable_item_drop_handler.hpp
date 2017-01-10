#ifndef PORTABLEITEMDROPHANDLER_HPP
#define PORTABLEITEMDROPHANDLER_HPP

#include "game/models/portable_item.hpp"

namespace game {

class PortableItemDropHandler
{
  public:

    PortableItemDropHandler();
    virtual ~PortableItemDropHandler() = default;

    virtual void add(PortableItemSP& item, const sf::Vector2i& pos) = 0;
    virtual void remove(PortableItemSP& item) = 0;    

  protected:

    std::vector<game::PortableItemSP> _items;
};

}

#endif // PORTABLEITEMDROPHANDLER_HPP
