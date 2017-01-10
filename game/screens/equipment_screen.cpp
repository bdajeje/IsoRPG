#include "equipment_screen.hpp"
#include "managers/texture_manager.hpp"
#include "managers/window.hpp"
#include "game/models/characters_team.hpp"
#include "graphics/animations/move.hpp"
#include "utils/graphics.hpp"

#include <limits>
#include <iostream>

namespace game {
namespace screen {

EquipmentScreen::EquipmentScreen()
  : _limitor {50}
{
  const unsigned int window_width  = mgr::Window::width();
  const unsigned int window_height = mgr::Window::height();

  graphics::RectangleSP shadow_background = std::make_shared<graphics::Rectangle>();
  shadow_background->shape()->setFillColor(sf::Color{0, 0, 0, 150});
  shadow_background->shape()->setSize(sf::Vector2f{window_width, window_height});
  addDrawable(shadow_background);

  _character_standing = std::make_shared<graphics::Sprite>(434, 511);
  _character_standing->setPosition(295, 20);
  addDrawable(_character_standing);

  const float thumbnail_x = 693;
  _character_faces.reserve(CharactersTeam::MaxNbrCharacters);
  _character_thumbnails.reserve(CharactersTeam::MaxNbrCharacters);
  for(size_t i = 0; i < CharactersTeam::MaxNbrCharacters; ++i)
  {
    auto character_thumbnail = graphics::getSprite("equipment_menu/character_not_selected.png", 0.1, 0.08);
    _character_thumbnails.push_back( character_thumbnail );
    const float thumbnail_y = 40 + i * 85;
    character_thumbnail->setPosition(thumbnail_x, thumbnail_y);

    auto character_face = std::make_shared<graphics::Sprite>(76, 73);
    character_face->setPosition( thumbnail_x + 25, thumbnail_y + 10 );
    _character_faces.push_back( character_face );

    addDrawable(character_face);
    addDrawable(character_thumbnail);

    addHoverable(character_thumbnail,
      [this, i, character_thumbnail]()
      {
        if(selectedCharacter() != i)
        {
          const sf::Texture& texture = texture::TextureManager::get("equipment_menu/character_selected.png");
          if(&texture != character_thumbnail->getTexture())
            character_thumbnail->setTexture(texture);
        }
      },
      [this, i, character_thumbnail]()
      {
        if(selectedCharacter() != i)
        {
          const sf::Texture& texture = texture::TextureManager::get("equipment_menu/character_not_selected.png");
          if(&texture != character_thumbnail->getTexture())
            character_thumbnail->setTexture(texture);
        }
      }
    );

    addClickable(character_thumbnail, [this, i](){ showPlayer(i); });
  }

  graphics::SpriteSP background = graphics::getSprite("equipment_menu/background.png", 0.7, 1);
  background->setPosition((window_width - background->getGlobalBounds().width) / 2, 0);
  addDrawable(background);

  _exp_bar = std::make_shared<graphics::Rectangle>();
  _exp_bar->shape()->setPosition(399, 405);
  _exp_bar->shape()->setFillColor(sf::Color{211, 191, 128});
  addDrawable(_exp_bar);

  _name_text = graphics::getText("Breathe_Fire.otf", "", 20, sf::Color::White);
  addDrawable(_name_text);

  _level_text = graphics::getText("Breathe_Fire.otf", "", 18, sf::Color::White);
  addDrawable(_level_text);

  _life_text = graphics::getText("Breathe_Fire.otf", "", 18, sf::Color::White);
  addDrawable(_life_text);

  _mana_text = graphics::getText("Breathe_Fire.otf", "", 18, sf::Color::White);
  addDrawable(_mana_text);

  _traits_text = graphics::getText("Breathe_Fire.otf", "", 20, sf::Color::White);
  addDrawable(_traits_text);

  _money_text = graphics::getText("Breathe_Fire.otf", "", 18, sf::Color::White);
  addDrawable(_money_text);
}

size_t EquipmentScreen::selectedCharacter() const noexcept
{
  return _selected_character;
}

void EquipmentScreen::showPlayer(size_t offset)
{
  constexpr float animation_x {20.f};

  if(_selected_character != std::numeric_limits<size_t>::max())
  {
    auto& character_thumbnail = _character_thumbnails[_selected_character];
    character_thumbnail->setTexture(texture::TextureManager::get("equipment_menu/character_not_selected.png"));
    auto hide_thumbnail_animation = std::make_shared<graphics::animations::Move>(character_thumbnail, -animation_x, 0, sf::milliseconds(200));
    addAnimation(hide_thumbnail_animation);
    auto hide_face_animation = std::make_shared<graphics::animations::Move>(_character_faces[_selected_character], -animation_x, 0, sf::milliseconds(200));
    addAnimation(hide_face_animation);
  }

  _selected_character = offset;
  _character_thumbnails[_selected_character]->setTexture(texture::TextureManager::get("equipment_menu/character_selected.png"));

  auto show_thumbnail_animation = std::make_shared<graphics::animations::Move>(_character_thumbnails[offset], animation_x, 0, sf::milliseconds(200));
  addAnimation(show_thumbnail_animation);
  auto show_face_animation = std::make_shared<graphics::animations::Move>(_character_faces[offset], animation_x, 0, sf::milliseconds(200));
  addAnimation(show_face_animation);

  const unsigned int window_width = mgr::Window::width();
  PlayableCharacterSP character = CharactersTeam::character(offset);
  _exp_bar->shape()->setSize(sf::Vector2f{character->expRatio() * 206.f, 5});

  _name_text->setString(character->name());
  _name_text->setPosition((window_width - _name_text->getGlobalBounds().width) / 2, 5);

  _level_text->setString("Level " + std::to_string(character->level()));
  _level_text->setPosition(330, 420);

  _life_text->setString("Life " + std::to_string(character->life()) + " / " + std::to_string(character->maxLife()));
  _life_text->setPosition(330, 440);

  _mana_text->setString("Mana " + std::to_string(character->mana()) + " / " + std::to_string(character->maxMana()));
  _mana_text->setPosition(330, 460);

  _traits_text->setString(character->traitName(0) + " / " + character->traitName(1));
  _traits_text->setPosition((window_width - _traits_text->getGlobalBounds().width) / 2, 372);

  _character_standing->setTexture(texture::TextureManager::get("characters/standings/" + character->standingTextureName()));
  utils::graphics::resize(_character_standing, 400, 343);

  const auto& current_character = CharactersTeam::character(_selected_character);
  _inventory = std::make_shared<Inventory>(current_character->inventory(), sf::Vector2f(200.f, 200.f));
  addDrawable(_inventory);
}

void EquipmentScreen::show()
{
  showPlayer(0);

  _money_text->setString(std::to_string(CharactersTeam::money()));
  _money_text->setPosition(695 - _money_text->getGlobalBounds().width, 877);

  const size_t nbr_characters = CharactersTeam::nbrCharacters();
  for(size_t i = 0; i < CharactersTeam::MaxNbrCharacters; ++i)
  {
    PlayableCharacterSP character = CharactersTeam::character(i);
    if(character)
    {
      _character_faces[i]->setTexture(texture::TextureManager::get(character->faceTextureName()));
      utils::graphics::resize(_character_faces[i], 50, 50);
    }

    if(i < nbr_characters)
    {
      _character_thumbnails[i]->show();
      _character_faces[i]->show();
    }
    else
    {
      _character_thumbnails[i]->hide();
      _character_faces[i]->hide();
    }
  }
}

void EquipmentScreen::update(const sf::Time& elapsed_time)
{
  InteractibleScreen::update(elapsed_time);
}

events::EventAction EquipmentScreen::handleEvents(const sf::Event& event)
{
  if(InteractibleScreen::handleEvents(event) == events::EventAction::Stop)
    return events::EventAction::Stop;

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wswitch"
  switch(event.type)
  {
    case sf::Event::KeyPressed:
    {
      if(isKeyAllowed(sf::Keyboard::Escape, _limitor))
        return events::EventAction::ExitScreen;

      break;
    }
  }
#pragma GCC diagnostic pop

  return events::EventAction::Stop;
}

}
}
