#include "map_ui.hpp"

#include "managers/window.hpp"
#include "managers/texture_manager.hpp"
#include "utils/file.hpp"
#include "game/game.hpp"
#include "game/screens/game_menu.hpp"

#include <iostream>

namespace game {
namespace screen {

static constexpr float ICON_WIDTH = 45;
static constexpr float ICON_HEIGHT = 45;
static constexpr float NAME_BG_WIDTH = 400;
static constexpr float NAME_BG_HEIGHT = 40;

MapUI::MapUI(const std::string& id, const json& data)
  : _id {id}
{
  // Map name add background
  auto name_background = graphics::getSprite("top_text_box.png", NAME_BG_WIDTH, NAME_BG_HEIGHT);
  name_background->setPosition((mgr::Window::width() - name_background->getGlobalBounds().width) / 2, 0);
  addDrawable(name_background);
  _map_name = graphics::getText("conversation.ttf", data["name"], 18, sf::Color(150, 150, 150));
  _map_name->setPosition((mgr::Window::width() - _map_name->getGlobalBounds().width) / 2, 5);
  addDrawable(_map_name);

  // Upper left icons
  auto equipment_icon = graphics::getSprite("equipment_icon.png", ICON_WIDTH, ICON_HEIGHT);
  auto team_icon = graphics::getSprite("team_icon.png", ICON_WIDTH, ICON_HEIGHT);
  auto skills_icon = graphics::getSprite("skills_icon.png", ICON_WIDTH, ICON_HEIGHT);
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
	  if(isKeyAllowed(utils::KeyBinding::key(KeyAction::ShowGameMenu)))
	  {
		Game::show(std::make_shared<screen::GameMenu>());
		return events::EventAction::Stop;
	  }
	  else if(isKeyAllowed(utils::KeyBinding::key(KeyAction::MapOpenInventory)))
	  {
		showEquipment();
		return events::EventAction::Stop;
	  }

	  break;
	}
  }
#pragma GCC diagnostic pop

  return events::EventAction::Continue;
}

}
}
