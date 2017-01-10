#ifndef INVENTORY_HPP
#define INVENTORY_HPP

#include <memory>
#include <map>
#include <vector>

#include "game/models/portable_item_drop_handler.hpp"
#include "game/models/portable_item.hpp"
#include "game/models/inventory_model.hpp"
#include "graphics/drawable.hpp"
#include "graphics/sprite.hpp"
#include "utils/serializable.hpp"

namespace graphics {

struct InventoryTile
{
    InventoryTile(SpriteSP& sprite)
      : _sprite {sprite}
    {}

    SpriteSP _sprite;
    game::PortableItemSP item;
};

class Inventory final : public game::PortableItemDropHandler
                      , public graphics::Drawable
                      , public utils::Serializable
{
  public:

//    static InventorySP create(const json& data, const sf::Vector2f& position);
    Inventory(game::InventoryModelSP model, const sf::Vector2f& position);

//    void addItems(std::vector<game::PortableItemSP>& items);
    void add(game::PortableItemSP& item, const sf::Vector2i& pos) override;
    void remove(game::PortableItemSP& item);
    void takeAll(std::shared_ptr<Inventory> from_inventory);
    size_t width() const noexcept { return _model->width(); }
    size_t height() const noexcept { return _model->height(); }
    virtual sf::FloatRect getGlobalBounds() const override;

    /*! Find first available space in inventory for a given item
     *  \param item - to find a space for
     *  \returns found space. If not space is available, returned value is {-1, -1}
     */
    sf::Vector2i findSpaceFor(const game::PortableItemSP& item);

    void clear();

    float pixelHeight() const { return _tiles.size() * _tiles[0][0]._sprite->getGlobalBounds().height; }
    std::vector<game::PortableItemSP> items() const;

    json save() override;

    virtual void setColor(const sf::Color& /*color*/) override {}
    virtual const sf::Color getColor() const override { return {}; }

  protected:

    bool isEmptySpace(size_t x, size_t y, const sf::Vector2i& iztem_size) const noexcept;
    virtual void internalDraw(sf::RenderTarget& target, sf::RenderStates states) const noexcept override;

  private:

    std::map<game::PortableItemSP, SpriteSP> _item_sprites;
    std::vector<std::vector<InventoryTile>> _tiles;
    sf::Vector2f _position;
    sf::FloatRect _slot_bounds;
    game::InventoryModelSP _model;
};

using InventorySP = std::shared_ptr<Inventory>;

}

#endif // INVENTORY_HPP
