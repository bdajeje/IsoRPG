#include "combat_ui.hpp"

#include "game/models/characters_team.hpp"
#include "graphics/sprite.hpp"
#include "graphics/models/fill_bar.hpp"
#include "graphics/animations/fill_color.hpp"
#include "graphics/animations/fading_animation.hpp"
#include "graphics/animations/fill_bar_animation.hpp"
#include "utils/graphics.hpp"
#include "managers/window.hpp"
#include "game/game.hpp"

namespace game {
namespace screen {

namespace {
  constexpr float FACE_WIDTH = 60;
  constexpr float FACE_HEIGHT = 60;
}

CombatUI::CombatUI(CombatModelSP model, graphics::TilesLayoutSP tiles_layout)
  : _model {model}
  , _tiles_layout {tiles_layout}
{
  using namespace graphics;

  const sf::Vector2f character_ui_pos {20, 20};
  float y_pos = 0;

  const unsigned int window_width  = mgr::Window::width();
  const unsigned int window_height = mgr::Window::height();

  _shadow_background = std::make_shared<graphics::Rectangle>();
  _shadow_background->shape()->setFillColor(sf::Color{0, 0, 0, 0});
  _shadow_background->shape()->setSize(sf::Vector2f{window_width, window_height});
  _shadow_background->addAnimation(std::make_shared<graphics::animations::FillColor>(_shadow_background->shape(), sf::Color{0, 0, 0, 100}, sf::milliseconds(500)));
  addDrawable(_shadow_background);

  // Create charactes UI
  auto& characters = CharactersTeam::instance()->characters();
  for(const auto& character : characters)
  {
    SpriteSP face = getSprite(character->faceTextureName(), FACE_WIDTH, FACE_HEIGHT);
    const auto face_bounds = face->getGlobalBounds();
    face->setPosition(character_ui_pos.x, character_ui_pos.y + y_pos);
    auto fade_in_animation = std::make_shared<animations::FadingAnimation>(face, sf::milliseconds(750), animations::FadingAnimation::Type::In);
    face->addAnimation(fade_in_animation);
    addDrawable(face);

    const float pos_x = face->getPosition().x + face_bounds.width + 10;

    FillBarSP life_rect = std::make_shared<FillBar>(0, character->maxLife(), sf::Color::Red, sf::Color::Black, 100, 8);
    life_rect->setPosition(pos_x, face->getPosition().y);
    face->addAnimation(std::make_shared<animations::FadingAnimation>(life_rect, sf::milliseconds(750), animations::FadingAnimation::Type::In));
    face->addAnimation(std::make_shared<animations::FillBarAnimation>(life_rect, character->life(), sf::milliseconds(750)));
    addDrawable(life_rect);

    FillBarSP mana_rect = std::make_shared<FillBar>(0, character->maxMana(), sf::Color::Blue, sf::Color::Black, 100, 8);
    mana_rect->setPosition(pos_x, life_rect->getPosition().y + life_rect->getGlobalBounds().height + 5);
    face->addAnimation(std::make_shared<animations::FadingAnimation>(mana_rect, sf::milliseconds(750), animations::FadingAnimation::Type::In));
    face->addAnimation(std::make_shared<animations::FillBarAnimation>(mana_rect, character->mana(), sf::milliseconds(750)));
    addDrawable(mana_rect);

    y_pos = mana_rect->getPosition().y + mana_rect->getGlobalBounds().height;
  }

  // Create timeline
  std::list<game::CharacterSP> timeline_characters (CharactersTeam::instance()->characters().begin(), CharactersTeam::instance()->characters().end());
  timeline_characters.insert(timeline_characters.end(), _model->ennemies().begin(), _model->ennemies().end());
  _timeline = std::make_shared<CombatTimeLine>(sf::Vector2f{1480, 10}, _model);
  addDrawable(_timeline);

  // Create ennemy info panel
  _ennemy_panel = std::make_shared<CombatCharacterPanel>(sf::Vector2f{1450, 730});
  _ennemy_panel->hide();
  addDrawable(_ennemy_panel);

  // Create player info screen
  _character_screen = std::make_shared<CombatPlayerPanel>(sf::Vector2f{5, 740}, model, _tiles_layout);
  _character_screen->setCharacter(characters.front());
  Game::show(_character_screen);

  // Mode text
  _mode_txt = getText("conversation.ttf", "Placing mode", 30, sf::Color::White);
  _mode_txt->setPosition(300, 30);
  addDrawable(_mode_txt);

  // Start button
  _start_button = std::make_shared<Button>("START", TextProperties{sf::Color::White, "conversation.ttf", 20});
  _start_button->setPosition(_mode_txt->getPosition().x + _mode_txt->getGlobalBounds().width + 15, _mode_txt->getPosition().y);
  _start_button->hide();
  addDrawable(_start_button);
  addClickable(_start_button, [this]() {
    startFight();
  });
  addHoverable(_start_button,
    [=]() { /*_start_button->hover();*/ },
    [=]() { /*_start_button->unhover();*/ }
  );

  // Add current character
  auto current_character = game::CharactersTeam::instance()->currentCharacter();
  _tiles_layout->addCharacter(current_character);
  _starting_map_pos = current_character->mapPos();

  // Start placing characters
  _characters_to_place.insert(_characters_to_place.end(), characters.begin() + 1, characters.end());
  nextCharacterToPlace();
}

void CombatUI::startFight()
{
  _model->startFight();
  _shadow_background->addAnimation(std::make_shared<graphics::animations::FillColor>(_shadow_background->shape(), sf::Color{0, 0, 0, 0}, sf::milliseconds(250)));
  _mode_txt->hide();
  _start_button->hide();
}

void CombatUI::nextCharacterToPlace()
{
  if(_character_to_place)
  {
    auto tile = _tiles_layout->tileAtMapPos(_character_to_place->mapPos());
    if(tile)
      tile->resetLines();

    // Remove highlight effect on tiles from previous character selection
    auto tiles = _tiles_layout->getTilesAround(game::CharactersTeam::instance()->currentCharacter()->mapPos(), _character_to_place->startMovementRange());
    for(auto& tile : tiles)
      tile->resetFillColor();
  }

  if(_characters_to_place.empty())
  {
    _character_to_place.reset();
    _start_button->show();
    return;
  }

  _character_to_place = _characters_to_place.front();
  _character_to_place->show();
  _tiles_layout->addCharacter(_character_to_place);
  _character_screen->setCharacter(_character_to_place);

  // Highlight tiles where to put character
  auto tiles = _tiles_layout->getTilesAround(game::CharactersTeam::instance()->currentCharacter()->mapPos(), _character_to_place->startMovementRange());
  for(auto& tile : tiles)
    tile->setHighlighted();

  _characters_to_place.pop_front();
}

void CombatUI::update(const sf::Time& elapsed_time)
{
  InteractibleScreen::update(elapsed_time);
  _timeline->update(elapsed_time);
}

events::EventAction CombatUI::handlePlacementEvents(const sf::Event& event)
{
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wswitch"
  switch(event.type)
  {
    case sf::Event::MouseMoved:
    {
      if(_character_to_place)
      {
        const MapPos map_pos = _tiles_layout->mapPosFromMousePos(event.mouseMove.x, event.mouseMove.y);
        if(map_pos != _previous_hovered_pos)
        {
          auto previous_tile = _tiles_layout->tileAtMapPos(_previous_hovered_pos);
          if(previous_tile)
            previous_tile->resetLines();

          _previous_hovered_pos = map_pos;

          auto tile = _tiles_layout->tileAtMapPos(map_pos);
          if(_tiles_layout->isWalkable(map_pos) && _tiles_layout->isInside(_starting_map_pos, _character_to_place->startMovementRange(), map_pos))
          {
            tile->setMovementAllowed(true);
            _tiles_layout->position(_character_to_place->sprite(), map_pos);
          }
          else tile->setMovementAllowed(false);
        }
      }
      else
        focusCharacter(event.mouseMove.x, event.mouseMove.y, false);

      break;
    }
    case sf::Event::MouseButtonPressed:
    {
      if(event.mouseButton.button == sf::Mouse::Button::Left)
      {
        const MapPos map_pos = _tiles_layout->mapPosFromMousePos(event.mouseButton.x, event.mouseButton.y);
        if(_character_to_place && _tiles_layout->isWalkable(map_pos) && _tiles_layout->isInside(_starting_map_pos, _character_to_place->startMovementRange(), map_pos))
        {
          _character_to_place->setMapPos(map_pos);
          _tiles_layout->position(_character_to_place->sprite(), map_pos);
          nextCharacterToPlace();
        }
        else
          focusCharacter(event.mouseButton.x, event.mouseButton.y, true);
      }

      break;
    }
  }
#pragma GCC diagnostic pop

  return events::EventAction::Continue;
}

events::EventAction CombatUI::handleCombatEvents(const sf::Event& event)
{
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wswitch"
  switch(event.type)
  {
    case sf::Event::MouseMoved:
    {
      focusCharacter(event.mouseMove.x, event.mouseMove.y, false);
      break;
    }
    case sf::Event::MouseButtonPressed:
    {
      CharacterSP character = characterAtMousePos(event.mouseMove.x, event.mouseMove.y);
      if(character && !character->isAlly())
        _ennemy_panel->setCharacter(character, true);

      break;
    }
  }
#pragma GCC diagnostic pop

  return events::EventAction::Continue;
}

CharacterSP CombatUI::characterAtMousePos(int x, int y)
{
  const auto map_pos = _tiles_layout->mapPosFromMousePos(x, y);

  for(auto character : CharactersTeam::instance()->characters())
  {
    if(character->mapPos() == map_pos)
      return character;
  }

  for(auto character : _model->ennemies())
  {
    if(character->mapPos() == map_pos)
      return character;
  }

  return {};
}

void CombatUI::focusCharacter(int x, int y, bool stay_focused)
{
  CharacterSP character = characterAtMousePos(x, y);
  if(character)
  {
    if(!character->isAlly())
      _ennemy_panel->setCharacter(character, stay_focused);
  }
  else
    _ennemy_panel->unfocus(stay_focused);
}

events::EventAction CombatUI::handleEvents(const sf::Event& event)
{
  if(InteractibleScreen::handleEvents(event) == events::EventAction::Stop)
    return events::EventAction::Stop;

  switch(_model->currentMode())
  {
    case CombatModel::Mode::Placement:
      return handlePlacementEvents(event);
    case CombatModel::Mode::Combat:
      return handleCombatEvents(event);
  }

  return events::EventAction::Stop;
}

}
}
