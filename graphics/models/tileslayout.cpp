#include "tileslayout.hpp"
#include "managers/window.hpp"
#include "utils/file.hpp"
#include "graphics/animations/delay.hpp"
#include "graphics/animations/fill_color.hpp"
#include "game/models/characters_team.hpp"
#include "game/models/map_pos.hpp"

#include <boost/algorithm/string.hpp>

#include <assert.h>
#include <iostream>

namespace graphics {

namespace {

  sf::Vector2f cartesianToIsometric(sf::Vector2f cartesian_pos)
  {
    return { cartesian_pos.x - cartesian_pos.y,
           (cartesian_pos.x + cartesian_pos.y) / 2 };
  }

  sf::Vector2f isometricToCartesian(sf::Vector2f&& isometric_pos)
  {
    return { (2 * isometric_pos.y + isometric_pos.x) / 2,
             (2 * isometric_pos.y - isometric_pos.x) / 2 };
  }

}

TilesLayout::TilesLayout(const json& data)
{
  createTiles(data["tiles"]);
  createInteractibles(data["interactibles"]);

  _characters.push_back(game::CharactersTeam::currentCharacter());

//  showTilesNumber();
}

void TilesLayout::createTiles(const json& data)
{
  const size_t nbr_y {data.size()};

  // Tiles size
  const sf::Vector2u window_size = mgr::Window::instance()->getSize();
  _tile_width  = 55;
  _tile_height = _tile_width; // squares

  // Transformation applied on tiles
  _tiles_transformation.x = window_size.x / 2;
  _tiles_transformation.y = -static_cast<float>(window_size.y) / 2;

  _tiles.resize(nbr_y);
  _walkables.resize(nbr_y);

  for(size_t y = 0; y < nbr_y; ++y)
  {
    const size_t nbr_x {data[y].size()};
    _tiles[y].reserve(nbr_x);
    _walkables[y].reserve(nbr_x);

    for(size_t x = 0; x < nbr_x; ++x)
    {
      TileSP tile;

      // Skip that tile if we don't want to display it
      const std::string tile_file = data[y][x];
      if(!tile_file.empty())
      {
        const float pos_x = x * _tile_width;
        const float pos_y = y * _tile_height;
        tile = std::make_shared<Tile>(
          cartesianToIsometric(sf::Vector2f{pos_x, pos_y}) + _tiles_transformation,
          cartesianToIsometric(sf::Vector2f{pos_x, pos_y + _tile_height}) + _tiles_transformation,
          cartesianToIsometric(sf::Vector2f{pos_x + _tile_width, pos_y + _tile_height}) + _tiles_transformation,
          cartesianToIsometric(sf::Vector2f{pos_x + _tile_width, pos_y}) + _tiles_transformation,
          "./resources/tiles/" + tile_file);

        _walkables[y].push_back( tile && !tile->blocking() );
      }

      _tiles[y].push_back(tile);
    }
  }
}

void TilesLayout::createInteractibles(const json& data)
{
  for(auto& decoration_data : data)
  {
    const auto& pos = decoration_data["pos"];
    const std::pair<int, int> pair_pos(pos[0], pos[1]);
    const MapPos map_pos(pair_pos.first, pair_pos.second);
    const bool blocking = decoration_data["blocking"];
    const bool combat_hidden = decoration_data["combat_hidden"];
    const std::string sprite_file = decoration_data["file"];
    SpriteSP sprite = getSprite(sprite_file, decoration_data["width"], decoration_data["height"]);
    position(sprite, map_pos);
    MapInteractibleSP interactible = std::make_shared<MapInteractible>(sprite, blocking, combat_hidden);
    _interactibles.emplace(pair_pos, interactible);

    if(blocking)
      _walkables[pair_pos.second][pair_pos.first] = false;

    if(decoration_data.find("interactions") != decoration_data.end())
    {
      for(auto& interaction : decoration_data["interactions"])
        interactible->_interactions.push_back(game::Interaction::create(interaction, sprite));
    }
  }
}

void TilesLayout::internalDraw(sf::RenderTarget& target, sf::RenderStates states) const noexcept
{
  // Draw tiles
  for(size_t y = 0; y < _tiles.size(); ++y)
  {
    const size_t nbr = _tiles[y].size();
    for(size_t x = 0; x < nbr; ++x)
    {
      const TileSP& tile = _tiles[y][x];
      if(!tile)
        continue;

      // Draw tile
      tile->draw(target, states);
    }
  }

  // Draw decorations, pnjs and player
  for(size_t y = 0; y < _tiles.size(); ++y)
  {
    const size_t nbr = _tiles[y].size();
    for(size_t x = 0; x < nbr; ++x)
    {
      // Draw interactibles
      auto interactible_it = _interactibles.find(std::pair<int, int>(x, y));
      if(interactible_it != _interactibles.end())
       interactible_it->second->_drawable->draw(target, states);

      for(const auto& character : _characters)
      {
        const auto& map_pos = character->mapPos();
        if(map_pos.x == x && map_pos.y == y)
          character->draw(target, states);        
      }
    }
  }

  if(_show_grid && !_texts_pos.empty())
  {
    for(const TextSP& text : _texts_pos)
      text->draw(target, states);
  }
}

MapPos TilesLayout::mapPosFromMousePos(int x_pos, int y_pos) const noexcept
{
  x_pos -= _tiles_transformation.x;
  y_pos -= _tiles_transformation.y;

  const sf::Vector2f cartesian_pos = isometricToCartesian(sf::Vector2f{static_cast<float>(x_pos), static_cast<float>(y_pos)});
  int x = (cartesian_pos.x / _tile_height);
  int y = (cartesian_pos.y / _tile_height);

  return {x, y};
}

TileSP TilesLayout::tileAtMousePos(int x_pos, int y_pos) noexcept
{
  const MapPos map_pos = mapPosFromMousePos(x_pos, y_pos);
  return tileAtMapPos(map_pos);
}

TileSP TilesLayout::tileAtMapPos(const MapPos& map_pos) noexcept
{
  if(map_pos.x < 0 || map_pos.y < 0 ||
     map_pos.y >= static_cast<int>(_tiles.size()) ||
     map_pos.x >= static_cast<int>(_tiles[map_pos.y].size()))
    return {};

  return _tiles[map_pos.y][map_pos.x];
}

sf::Vector2f TilesLayout::tileToCartesian(size_t x, size_t y) const noexcept
{
  return { x * _tile_width,
           y * _tile_height };
}

TileSP TilesLayout::tileHovered(int x_pos, int y_pos)
{
  TileSP tile = tileAtMousePos(x_pos, y_pos);
  if(!tile)
    return {};

  if(tile == _previous_selected_tile)
    return tile;

  if(_previous_hovered_tile)
  {
    _previous_hovered_tile->unhover();

    // Also unhover all interactions on that tile
    auto interactibe_it = _interactibles.find(std::make_pair(x_pos, y_pos));
    if(interactibe_it != _interactibles.end())
    {
      for(auto& interaction : interactibe_it->second->_interactions)
        interaction->mouseLeave();
    }
  }

  triggerTileHovered(mapPosFromMousePos(x_pos, y_pos));

  _previous_hovered_tile = tile;

  if(!tile->blocking())
    tile->hover();

  return tile;
}

TileSP TilesLayout::tileClicked(const MapPos& map_pos)
{
  TileSP tile = tileAtMapPos(map_pos);
  if(!tile)
    return {};

  if(_previous_selected_tile)
    _previous_selected_tile->unselect();

  _previous_selected_tile = tile;
  tile->select();

  return tile;
}

void TilesLayout::showTilesNumber()
{
  for(size_t y = 0; y < _tiles.size(); ++y)
  {
    _texts_pos.reserve(_tiles[y].size());

    for(size_t x = 0; x < _tiles[y].size(); ++x)
    {
      TileSP& tile = _tiles[y][x];
      if(!tile)
        continue;

      TextSP text = getText("conversation.ttf", std::to_string(x) + "/" + std::to_string(y), 14, sf::Color::White);
      text->setPosition( tile->getPosition() );
      _texts_pos.push_back(text);
    }
  }
}

void TilesLayout::position(SpriteSP transformable, MapPos pos) const noexcept
{  
  const sf::Vector2f cartesian = tileToCartesian(pos.x, pos.y);
  sf::Vector2f isometric = cartesianToIsometric(cartesian);

  // Apply transformation
  isometric.x += _tiles_transformation.x;
  isometric.y += _tiles_transformation.y;

  // Place transformable at center of tile
  const sf::FloatRect bounds = transformable->getGlobalBounds();
  isometric.x -= _tile_width / 2;
  isometric.x -= (std::max(_tile_width, bounds.width) - std::min(_tile_width, bounds.width)) / 2;
  isometric.y -= bounds.height - _tile_height;

  transformable->setPosition( isometric );
}

bool TilesLayout::isValidPoint(const MapPos& point) const
{
  return point.y >= 0 && point.x >= 0 &&
         point.y < static_cast<int>(_tiles.size()) && point.x < static_cast<int>(_tiles[point.y].size()) &&
         _tiles[point.y][point.x];
}

Path TilesLayout::findPath(const MapPos& start, const MapPos& dest) const
{
  // Create a copy of the map so we know which points have already been visited (consider non-walkable points as visited ones)
  // For now only check map tiles.
  // \todo also check for pnj and other possible things on the tile that blocks it.
  std::vector<std::vector<bool>> visited_points = _walkables;

  std::list<Path> result_paths = { {start} };
  while(!result_paths.empty())
  {
    for(auto it = result_paths.begin(), end = result_paths.end(); it != end; ++it)
    {
      Path& result_path = *it;

      // Did we find the destination point? If yes return right now cause this path is the fastest one
      if(result_path.back() == dest)
      {
        result_path.pop_front(); // first is starting point, no need of it
        return result_path;
      }

      const std::vector<MapPos> neighbour_points = findNeighours(visited_points, result_path);
      const size_t nbr_neighbours = neighbour_points.size();

      // Path leads to nowhere, remove path
      if(nbr_neighbours == 0)
      {
        result_paths.erase(it);

        // Because we removed a path while iterating on paths, make sure we don't break the loop
        --it;
      }
      else
      {
        // Add first solution to current path
        result_path.push_back(neighbour_points[0]);

        // Create a new path for all other possible neighbours
        for(size_t i = 1; i < nbr_neighbours; ++i)
        {
          // Access current path by memory offset here because previous reference might be invalid at this point
          Path new_path = *it;
          new_path.back() = neighbour_points[i];
          result_paths.push_back( std::move(new_path) );
        }
      }
    }
  }

  // If we goes to this point it means there is no possible path between start and dest.
  return {};
}

bool TilesLayout::isWalkable(const MapPos& dest) const
{
  return _walkables[dest.y][dest.x];
}

Path TilesLayout::pathFinding(const MapPos& start, const MapPos& dest)
{
  if(!isValidPoint(dest))
  {
    std::cout << "Destination point unreachable" << std::endl;
    return {};
  }

  // If target destination is interactible and blocking,
  // temporary make destination tile non-blockable to find a path to it,
  // then make it blocking again
  const bool path_to_interactible = !isWalkable(dest) && isInteractible(dest);
  if(path_to_interactible)
    _walkables[dest.y][dest.x] = true;

  Path path = findPath(start, dest);
  enlightPath(path);

  if(path_to_interactible)
    _walkables[dest.y][dest.x] = false;

  return path;
}

std::vector<MapPos> TilesLayout::findNeighours(std::vector<std::vector<bool>>& visited_points, const Path& path) const
{
  const MapPos& current_point = path.back();
  const std::array<MapPos, 4> neighbours_points {
    MapPos{current_point.x - 1, current_point.y},
    MapPos{current_point.x + 1, current_point.y},
    MapPos{current_point.x, current_point.y - 1},
    MapPos{current_point.x, current_point.y + 1}
  };

  std::vector<MapPos> valid_neighbours_points;
  valid_neighbours_points.reserve(neighbours_points.size());

  for(const MapPos& neighbour_point : neighbours_points)
  {
    if( isValidPoint(neighbour_point) && !_tiles[neighbour_point.y][neighbour_point.x]->blocking() &&
        visited_points[neighbour_point.y][neighbour_point.x] != false &&
        std::find(path.begin(), path.end(), neighbour_point) == path.end() )
    {
      valid_neighbours_points.push_back( neighbour_point );
      visited_points[neighbour_point.y][neighbour_point.x] = false;
    }
  }

  return valid_neighbours_points;
}

void TilesLayout::enlightPath(const Path& path)
{
  // Finish previous animations
  for(AnimationSP& animation : _enlighted_tile_animations)
    animation->finish();

  unEnlightedTiles();
  _enlighted_tiles.clear();
  _enlighted_tile_animations.clear();

  // Create new animations
  int delay {0};
  for(const MapPos& map_pos: path)
  {
    TileSP tile = tileAtMapPos(map_pos);
    if(tile)
    {
      std::shared_ptr<sf::Shape> shape = tile->shape();
      AnimationSP enlight_animation = std::make_shared<animations::FillColor>(shape, sf::Color{255, 255, 255, 100}, sf::milliseconds(300));
      auto delay_animation = std::make_shared<animations::Delay>(enlight_animation, sf::milliseconds(delay));
      _enlighted_tiles.push_back(tile);
      _animations.push_back(delay_animation);
      _enlighted_tile_animations.push_back(enlight_animation);
    }

    delay += 5;
  }
}

void TilesLayout::update(const sf::Time& elapsed_time)
{
  // Update tiles
  for(const auto& tiles : _tiles)
  {
    for(const auto& tile : tiles)
    {
      if(tile)
        tile->update(elapsed_time);
    }
  }

  // Update interactibles
  for(const auto& interactible : _interactibles)
    interactible.second->_drawable->update(elapsed_time);

  // Update animations
  for(AnimationSP& animation : _animations)
    animation->update(elapsed_time);

  // Removed finished animations
  _animations.erase(std::remove_if(_animations.begin(), _animations.end(), [](const AnimationSP& animation){
    return animation->isFinished();
  }), _animations.end());
}

void TilesLayout::unEnlightedTiles()
{
  for(const TileSP& tile: _enlighted_tiles)
  {
    std::shared_ptr<sf::Shape> shape = tile->shape();
    AnimationSP animation = std::make_shared<animations::FillColor>(shape, sf::Color{255, 255, 255, 0}, sf::milliseconds(100));
    _animations.push_back(animation);
  }
}

void TilesLayout::toggleShowGrid() noexcept
{
  _show_grid = !_show_grid;

  for(const auto& line : _tiles)
  {
    for(const TileSP& tile : line)
    {
      if(tile)
        tile->toggleShowGrid();
    }
  }
}

void TilesLayout::triggerTileHovered(const MapPos& map_pos)
{
  auto interaction_it = _interactibles.find(std::make_pair(map_pos.x, map_pos.y));
  if(interaction_it != _interactibles.end())
  {
    MapInteractibleSP interactible = interaction_it->second;
    for(game::InteractionSP& interaction : interactible->_interactions)
      interaction->mouseHover();
  }
}

void TilesLayout::triggerInteraction(const MapPos& map_pos)
{
  auto interaction_it = _interactibles.find(std::make_pair(map_pos.x, map_pos.y));
  if(interaction_it != _interactibles.end())
  {
    MapInteractibleSP interactible = interaction_it->second;
    for(game::InteractionSP& interaction : interactible->_interactions)
      game::Interaction::send(interaction);
  }
}

json TilesLayout::save()
{
  // \todo
  json data;
  return data;
}

void TilesLayout::startCombat(game::CombatModelSP& model)
{
  _characters.clear();
  _combat_model = model;

  // Hide interactibles for combat
  for(auto& interactible_it : _interactibles)
  {
    MapInteractibleSP& interactible = interactible_it.second;
    if(interactible->_is_combat_hidden)
      interactible->_drawable->hide();
  }

  // Add combat interactibles (ennemies...)
  for(auto& ennemy : model->ennemies())
    addEnnemy(ennemy);  
}

void TilesLayout::addEnnemy(game::EnnemyCharacterSP& ennemy)
{
  _characters.push_back(ennemy);
  position(ennemy->sprite(), ennemy->mapPos());
}

bool TilesLayout::isInside(const MapPos& center_map_pos, int radius, const MapPos& map_pos) const
{
  return std::abs(center_map_pos.x - map_pos.x) <= radius && std::abs(center_map_pos.y - map_pos.y) <= radius;
}

std::vector<graphics::TileSP> TilesLayout::getTilesAround(const MapPos& map_pos, int radius) const
{
  std::vector<graphics::TileSP> tiles;

  const size_t min_x = std::max(0, map_pos.x - radius);
  const size_t min_y = std::max(0, map_pos.y - radius);
  const size_t max_y = std::min(static_cast<int>(_tiles.size()) - 1, map_pos.y + radius);

  for(size_t y = min_y; y <= max_y; ++y)
  {
    const size_t max_x = std::min(static_cast<int>(_tiles[y].size()) - 1, map_pos.x + radius);
    for(size_t x = min_x; x <= max_x; ++x)
    {
      if(_tiles[y][x])
        tiles.push_back(_tiles[y][x]);
    }
  }

  return tiles;
}

sf::FloatRect TilesLayout::getGlobalBounds() const
{
  const auto window_size = mgr::Window::instance()->getSize();
  return {0, 0, window_size.x, window_size.y};
}

}
