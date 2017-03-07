#include "treasure_screen.hpp"
#include "graphics/mouse.hpp"
#include "game/models/characters_team.hpp"

namespace game {
namespace screen {

TreasureScreen::TreasureScreen(TreasureInteractionSP interaction)
  :_interaction {interaction}
{
  using namespace graphics;

  // Treasure inventory
  const sf::Vector2f _treasure_inventory_pos = sf::Vector2f(400, 400);
  _treasure_inventory = std::make_shared<Inventory>(interaction->model(), _treasure_inventory_pos);
  addDrawable(_treasure_inventory);

  // Quit button
  SpriteSP quit_button = getSprite("quit_button.png", 25, 25);
  quit_button->setPosition(_treasure_inventory_pos.x, _treasure_inventory_pos.y + _treasure_inventory->pixelHeight() + 15);
  addDrawable(quit_button);
  addHoverable(quit_button,
   [this](){ graphics::Mouse::setStatus(graphics::Mouse::Status::Hover); },
   [this](){ graphics::Mouse::setStatus(graphics::Mouse::Status::Normal); });
  addClickable(quit_button,
    [this](){ _finish = true; });

  // Players inventory
  const float x_pos = 800;
  float y_pos = 100;
  for(const auto& character : CharactersTeam::instance()->characters())
  {
    auto character_portrait = getSprite(character->faceTextureName(), 80, 80);
    character_portrait->setPosition(x_pos, y_pos);
    addDrawable(character_portrait);

    auto character_inventory = std::make_shared<Inventory>(character->inventory(), sf::Vector2f(x_pos + character_portrait->getGlobalBounds().width + 15, y_pos));
    _inventories[character] = character_inventory;
    addDrawable(character_inventory);

    auto take_all_arrow = getSprite("right_arrow.png", 40, 40);
    take_all_arrow->setPosition(x_pos + ((character_portrait->getGlobalBounds().width - take_all_arrow->getGlobalBounds().width) / 2), y_pos + character_portrait->getGlobalBounds().height + 15);
    addDrawable(take_all_arrow);
    addHoverable(take_all_arrow,
     [this](){ graphics::Mouse::setStatus(graphics::Mouse::Status::Hover); },
     [this](){ graphics::Mouse::setStatus(graphics::Mouse::Status::Normal); });
    addClickable(take_all_arrow,
      [=](){ character_inventory->takeAll(_treasure_inventory); });

    y_pos += character_inventory->pixelHeight() + 50;
  }
}

TreasureScreen::~TreasureScreen()
{
  for(auto& character : CharactersTeam::instance()->characters())
    character->inventory()->setItems( _inventories[character]->items() );

  _interaction->setItems(_treasure_inventory->items());
}

events::EventAction TreasureScreen::handleEvents(const sf::Event &event)
{
  if(InteractibleScreen::handleEvents(event) == events::EventAction::Stop)
    return events::EventAction::Stop;

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wswitch"
  switch(event.type)
  {
    case sf::Event::KeyPressed:
    {
      if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        return events::EventAction::ExitScreen;
    }
  }
#pragma GCC diagnostic pop

  return events::EventAction::Stop;
}

}
}
