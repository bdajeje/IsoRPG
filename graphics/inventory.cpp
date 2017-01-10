#include "inventory.hpp"
#include "utils/graphics.hpp"

#include <iostream>

namespace graphics {

namespace {
  constexpr float INVENTORY_SLOT_WIDTH = 50;
  constexpr float INVENTORY_SLOT_HEIGHT = 50;
}

Inventory::Inventory(game::InventoryModelSP model, const sf::Vector2f& position)
  : _position {position}
  , _model {model}
{
  const size_t width = _model->width();
  float y_pos = position.y;
  _tiles.resize(_model->height());
  for(auto& line : _tiles)
  {
    float x_pos = position.x;
    line.reserve(width);
    for(size_t i = 0; i < width; ++i)
    {
      auto sprite = getSprite("inventory_slot.png", INVENTORY_SLOT_WIDTH, INVENTORY_SLOT_HEIGHT);
      sprite->setPosition(x_pos, y_pos);
      line.emplace_back(sprite);
      x_pos += INVENTORY_SLOT_WIDTH;
    }

    y_pos += INVENTORY_SLOT_HEIGHT;
  }

  for(auto& item : _model->items())
    add(item, item->posInContainer());
}

void Inventory::add(game::PortableItemSP& item, const sf::Vector2i& inventory_pos)
{
  const auto& item_size = item->inventorySize();

  auto sprite = getSprite(item->textureFileName(), INVENTORY_SLOT_WIDTH * item_size.x, INVENTORY_SLOT_HEIGHT * item_size.y);
  sprite->setPosition(_position.x + inventory_pos.x * _slot_bounds.width,
                      _position.y + inventory_pos.y * _slot_bounds.height);
  _item_sprites.emplace(item, sprite);

  for(size_t y = inventory_pos.y, y_end = inventory_pos.y + item_size.y; y < y_end; ++y)
  {
    for(size_t x = inventory_pos.x, x_end = inventory_pos.x + item_size.x; x < x_end; ++x)
      _tiles[y][x].item = item;
  }

  item->setInventoryPos(inventory_pos);
}

void Inventory::remove(game::PortableItemSP& item)
{
  _item_sprites.erase( _item_sprites.find(item) );

  const auto& item_pos  = item->posInContainer();
  const auto& item_size = item->inventorySize();
  for(size_t y = item_pos.y, y_end = item_pos.y + item_size.y; y < y_end; ++y)
  {
    for(size_t x = item_pos.x, x_end = item_pos.x + item_size.x; x < x_end; ++x)
      _tiles[y][x].item = nullptr;
  }
}

bool Inventory::isEmptySpace(size_t x, size_t y, const sf::Vector2i& item_size) const noexcept
{
  const size_t max_x = std::min(_model->width(), x + item_size.x);
  const size_t max_y = std::min(_model->height(), x + item_size.y);

  for(; y < max_y; ++y)
  {
    for(; x < max_x; ++x)
    {
      if(!_tiles[y][x]._sprite)
        return false;
    }
  }

  return true;
}

void Inventory::internalDraw(sf::RenderTarget& target, sf::RenderStates states) const noexcept
{
  for(const auto& line : _tiles)
  {
    for(const auto& tile : line)
      tile._sprite->draw(target, states);
  }

  for(const auto& sprite : _item_sprites)
    sprite.second->draw(target, states);
}

void Inventory::clear()
{
  _item_sprites.clear();
}

sf::Vector2i Inventory::findSpaceFor(const game::PortableItemSP& item)
{
  const auto& item_size = item->inventorySize();

  if(item_size.y > _tiles.size() || item_size.x > _tiles[0].size())
    return {-1, -1};

  for(size_t y = 0, y_end = _tiles.size() - item_size.y; y <= y_end; ++y)
  {
    for(size_t x = 0, x_end = _tiles[y].size() - item_size.x; x <= x_end; ++x)
    {
      bool free = true;
      for(size_t y_height = 0, height_end = item_size.y; y_height < height_end; ++y_height)
      {
        for(size_t x_width = 0, width_end = item_size.x; x_width < width_end; ++x_width)
        {
          if(_tiles[y + y_height][x + x_width].item)
          {
            free = false;
            break;
          }
        }
      }

      if(free)
        return {x, y};
    }
  }

  return {-1, -1};
}

void Inventory::takeAll(InventorySP from_inventory)
{
  auto items = from_inventory->items();
  for(auto& item : items)
  {
    const sf::Vector2i available_space = findSpaceFor(item);
    if(available_space.x != -1 && available_space.y != -1)
    {
      from_inventory->remove(item);
      add( item, available_space );
    }
  }
}

std::vector<game::PortableItemSP> Inventory::items() const
{
  std::vector<game::PortableItemSP> result;
  result.reserve(_item_sprites.size());

  for(auto& it : _item_sprites)
    result.push_back( it.first );

  return result;
}

json Inventory::save()
{
  json data;
  auto& inventory = data["inventory"];
  inventory["inventory_max_height"] = height();
  inventory["inventory_max_width"] = width();
  for(const auto& item : _items)
    inventory["items"] = item->save();

  return data;
}

sf::FloatRect Inventory::getGlobalBounds() const
{
  return {_position.x, _position.y, width(), height()};
}

}
