#include "map.hpp"

#include "graphics/animation.hpp"
#include "utils/file.hpp"
#include "utils/random.hpp"
#include "managers/texture_manager.hpp"
#include "managers/music_manager.hpp"
#include "game/models/characters_team.hpp"
#include "game/game.hpp"
#include "game/screens/combat_ui.hpp"

namespace game {
namespace screen {

namespace actions {
  constexpr size_t ShowEquipment {0};
}

CombatPhase::CombatPhase(const json& data)
  : _data {data}
{
  if(data.find("music") != data.end())
    _music = data["music"];
}

Map::Map(const json& data)
  : _limitor {50}
  , _tiles_layout {std::make_shared<graphics::TilesLayout>(data)}
{  
  const MapPos starting_pos = MapPos(data["starting_map_pos"][0], data["starting_map_pos"][1]);
  CharactersTeam::currentCharacter()->setMapPos(starting_pos);
  _tiles_layout->position(CharactersTeam::currentCharacter()->sprite(), starting_pos);
  addDrawable(_tiles_layout);

  // Start music if any
  if(!data["music"].empty())
    manager::MusicManager::instance().play(data["music"]);

  // Create combats instances
  _combat_probability = data["combats"]["probability"];
  for(const auto& combat_data : data["combats"]["combat_groups"])
    _combats.emplace_back(combat_data);
}

void Map::update(const sf::Time& elapsed_time)
{
  InteractibleScreen::update(elapsed_time);
  _tiles_layout->update(elapsed_time);

  switch(_current_mode)
  {
    case MapMode::Combat:
      updateCombat(elapsed_time); break;
    case MapMode::Visit:
      updateVisit(elapsed_time); break;
  }
}

void Map::updateCombat(const sf::Time& elapsed_time)
{

}

void Map::updateVisit(const sf::Time& elapsed_time)
{
  // Move player sprite
  PlayableCharacterSP& current_character = CharactersTeam::currentCharacter();
  if(!_player_path.empty() && !current_character->isMoving())
  {
    const MapPos target_map_pos = _player_path.front();
    if(_tiles_layout->isWalkable(target_map_pos))
    {
      current_character->moveTo(target_map_pos, _tiles_layout->tileAtMapPos(target_map_pos)->getPosition());
      _player_path.pop_front();

      triggerCombatChance();

      if(_player_path.empty())
        _tiles_layout->triggerInteraction(target_map_pos);
    }
    else
    {
      // If we are at one point from target, try to activate it
      if(_player_path.size() == 1)
        _tiles_layout->triggerInteraction(_player_path.front());

      _player_path.clear();
    }
  }

  current_character->update(elapsed_time);
}

events::EventAction Map::handleEvents(const sf::Event& event)
{
  if(InteractibleScreen::handleEvents(event) == events::EventAction::Stop)
    return events::EventAction::Stop;

  switch(_current_mode)
  {
    case MapMode::Combat:
      return handleCombatEvents(event);
    case MapMode::Visit:
      return handleVisitEvents(event);
  }

  return events::EventAction::Continue;
}

events::EventAction Map::handleVisitEvents(const sf::Event& event)
{
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wswitch"
  switch(event.type)
  {
    case sf::Event::KeyPressed:
    {
      if(isKeyAllowed(sf::Keyboard::T, _limitor))
        _tiles_layout->toggleShowGrid();

      break;
    }
    case sf::Event::MouseMoved:
    {
      _tiles_layout->tileHovered(event.mouseMove.x, event.mouseMove.y);
      break;
    }
    case sf::Event::MouseButtonPressed:
    {
      const MapPos map_pos = _tiles_layout->mapPosFromMousePos(event.mouseButton.x, event.mouseButton.y);
      graphics::TileSP tile = _tiles_layout->tileClicked(map_pos);
      if(tile && (!tile->blocking() || _tiles_layout->isInteractible(map_pos)))
        _player_path = _tiles_layout->pathFinding(CharactersTeam::currentCharacter()->mapPos(), map_pos);
      break;
    }
    case sf::Event::MouseButtonReleased:
    {
      break;
    }
  }
#pragma GCC diagnostic pop

  return events::EventAction::Continue;
}

events::EventAction Map::handleCombatEvents(const sf::Event& event)
{
  return events::EventAction::Continue;
}

json Map::save()
{
  json data = _tiles_layout->save();
  return data;
}

void Map::triggerCombatChance()
{
  if(utils::random(0, 100) > _combat_probability)
    return;

  const CombatPhase& combat_phase = _combats[ utils::random(0, _combats.size() - 1) ];
  startCombat(combat_phase);
}

void Map::startCombat(const CombatPhase& combat_phase)
{
  _current_mode = MapMode::Combat;
  _combat_model = std::make_shared<CombatModel>(combat_phase._data);
  _tiles_layout->startCombat(_combat_model);

  Game::hideMapUI();
  Game::show(std::make_shared<screen::CombatUI>(_combat_model, _tiles_layout));

  if(!combat_phase._music.empty())
    manager::MusicManager::instance().play(combat_phase._music);
}

}
}
