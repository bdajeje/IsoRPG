#include "map_ui.hpp"

#include "managers/window.hpp"
#include "managers/texture_manager.hpp"
#include "utils/file.hpp"
#include "game/game.hpp"
#include "game/screens/game_menu.hpp"

#include <iostream>

namespace game {
namespace screen {

MapUI::MapUI(const std::string& id, const json& data)
  : _id {id}
  , _limitor {50}
{
  // Map name add background
  auto name_background = graphics::getSprite("top_text_box.png", 0.35, 0.05);
  name_background->setPosition((mgr::Window::width() - name_background->getGlobalBounds().width) / 2, 0);
  addDrawable(name_background);
  _map_name = graphics::getText("conversation.ttf", data["name"], 16, sf::Color(100, 100, 100));
  _map_name->setPosition((mgr::Window::width() - _map_name->getGlobalBounds().width) / 2, 5);
  addDrawable(_map_name);

  // Upper left icons
  auto equipment_icon = graphics::getSprite("equipment_icon.png", 0.03, 0.03);
  auto team_icon = graphics::getSprite("team_icon.png", 0.03, 0.03);
  auto skills_icon = graphics::getSprite("skills_icon.png", 0.03, 0.03);
  std::vector<graphics::SpriteSP> icon_paths = {equipment_icon, team_icon, skills_icon};
  float x {0};
  for(graphics::SpriteSP& icon : icon_paths)
  {
    icon->setPosition(x, 0);
    x += icon->getGlobalBounds().width;
    addDrawable(icon);
  }

  _equipment_page = std::make_shared<EquipmentScreen>();

  addHoverable(equipment_icon,
   [this, equipment_icon](){ equipment_icon->setTexture( texture::TextureManager::get("equipment_icon_hover.png") ); },
   [this, equipment_icon](){ equipment_icon->setTexture( texture::TextureManager::get("equipment_icon.png") ); }
  );
  addHoverable(team_icon,
   [this, team_icon](){ team_icon->setTexture( texture::TextureManager::get("team_icon_hover.png") ); },
   [this, team_icon](){ team_icon->setTexture( texture::TextureManager::get("team_icon.png") ); }
  );
  addHoverable(skills_icon,
   [this, skills_icon](){ skills_icon->setTexture( texture::TextureManager::get("skills_icon_hover.png") ); },
   [this, skills_icon](){ skills_icon->setTexture( texture::TextureManager::get("skills_icon.png") ); }
  );

  addClickable(equipment_icon, [&](){showEquipment();});
  addClickable(team_icon, [&](){showTeam();});
  addClickable(skills_icon, [&](){showSkills();});
}

void MapUI::update(const sf::Time& elapsed_time)
{
  InteractibleScreen::update(elapsed_time);
}

void MapUI::showEquipment() const noexcept
{
  Game::show(_equipment_page);
}

void MapUI::showTeam() const noexcept
{
  std::cout << "show team" << std::endl;
}

void MapUI::showSkills() const noexcept
{
  std::cout << "show skills" << std::endl;
}

events::EventAction MapUI::handleEvents(const sf::Event& event)
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
        Game::show(std::make_shared<screen::GameMenu>());
      else if(isKeyAllowed(sf::Keyboard::I, _limitor))
        showEquipment();

      break;
    }
  }
#pragma GCC diagnostic pop

  return events::EventAction::Continue;
}

}
}
