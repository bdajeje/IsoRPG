#ifndef PORTABLEITEM_HPP
#define PORTABLEITEM_HPP

#include <memory>
#include <SFML/System.hpp>

#include "graphics/sprite.hpp"
#include "utils/serializable.hpp"

namespace game {

class PortableItem;
using PortableItemSP = std::shared_ptr<PortableItem>;

class PortableItem : public utils::Serializable
{
  public:

    static PortableItemSP create(const json& data);

    const sf::Vector2i& inventorySize() const { return _inventory_size; }
    const sf::Vector2i& posInContainer() const { return _pos_in_container; }
    const std::string& textureFileName() const { return _texture_filename; }

    void setInventoryPos(const sf::Vector2i& pos) { _pos_in_container = pos; }

    virtual json save() override;

  protected:

    PortableItem(const json& data);

  protected:

    std::string _texture_filename;
    sf::Vector2i _inventory_size;
    sf::Vector2i _pos_in_container;
};

}

#endif // PORTABLEITEM_HPP
