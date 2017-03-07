#include "combat_character_panel.hpp"
#include "managers/texture_manager.hpp"

namespace graphics {

namespace {
  constexpr float PADDING = 20;
  constexpr float BACKGROUND_WIDTH = 300;
  constexpr float BACKGROUND_HEIGHT = 150;
  constexpr float ICON_WIDTH = 20;
  constexpr float ICON_HEIGHT = 20;
  constexpr float FACE_WIDTH = 50;
  constexpr float FACE_HEIGHT = 50;
  constexpr uint FONT_SIZE = 15;
}

CombatCharacterPanel::CombatCharacterPanel(const sf::Vector2f& pos)
{
  _background = getSprite("combats/ui_panel_background.png", BACKGROUND_WIDTH, BACKGROUND_HEIGHT);
  _transformable = _background->sprite();
  _face = std::make_shared<Sprite>(FACE_WIDTH, FACE_HEIGHT);

  _strengh_icon = getSprite("icons/strengh.png", ICON_WIDTH, ICON_HEIGHT);
  _endurance_icon = getSprite("icons/endurance.png", ICON_WIDTH, ICON_HEIGHT);
  _agility_icon = getSprite("icons/agility.png", ICON_WIDTH, ICON_HEIGHT);
  _intellect_icon = getSprite("icons/intellect.png", ICON_WIDTH, ICON_HEIGHT);
  _fire_icon = getSprite("icons/fire.png", ICON_WIDTH, ICON_HEIGHT);
  _ice_icon = getSprite("icons/ice.png", ICON_WIDTH, ICON_HEIGHT);
  _wind_icon = getSprite("icons/wind.png", ICON_WIDTH, ICON_HEIGHT);
  _hearth_icon = getSprite("icons/hearth.png", ICON_WIDTH, ICON_HEIGHT);

  _strengh = getText("conversation.ttf", "", FONT_SIZE, sf::Color::White);
  _endurance = getText("conversation.ttf", "", FONT_SIZE, sf::Color::White);
  _agility = getText("conversation.ttf", "", FONT_SIZE, sf::Color::White);
  _intellect = getText("conversation.ttf", "", FONT_SIZE, sf::Color::White);
  _fire = getText("conversation.ttf", "", FONT_SIZE, sf::Color::White);
  _ice = getText("conversation.ttf", "", FONT_SIZE, sf::Color::White);
  _wind = getText("conversation.ttf", "", FONT_SIZE, sf::Color::White);
  _hearth = getText("conversation.ttf", "", FONT_SIZE, sf::Color::White);

  setPosition(pos.x, pos.y);
}

void CombatCharacterPanel::internalDraw(sf::RenderTarget& target, sf::RenderStates states) const noexcept
{
  _background->draw(target, states);
  _face->draw(target, states);

  _strengh_icon->draw(target, states);
  _endurance_icon->draw(target, states);
  _agility_icon->draw(target, states);
  _intellect_icon->draw(target, states);
  _fire_icon->draw(target, states);
  _ice_icon->draw(target, states);
  _wind_icon->draw(target, states);
  _hearth_icon->draw(target, states);

  _strengh->draw(target, states);
  _endurance->draw(target, states);
  _agility->draw(target, states);
  _intellect->draw(target, states);
  _fire->draw(target, states);
  _ice->draw(target, states);
  _wind->draw(target, states);
  _hearth->draw(target, states);
}

void CombatCharacterPanel::setCharacter(game::CharacterSP character, bool stay_focused)
{
  const auto& attributes = character->attributes();
  _strengh->setString( std::to_string(attributes.strengh) );
  _endurance->setString( std::to_string(attributes.endurance) );
  _agility->setString( std::to_string(attributes.agility) );
  _intellect->setString( std::to_string(attributes.intellect) );
  _fire->setString( std::to_string(attributes.resistances.fire) );
  _ice->setString( std::to_string(attributes.resistances.ice) );
  _wind->setString( std::to_string(attributes.resistances.wind) );
  _hearth->setString( std::to_string(attributes.resistances.hearth) );
  _face->setTexture(texture::TextureManager::get(character->faceTextureName()));

  if(stay_focused)
    _focused_character = character;

  show();
}

void CombatCharacterPanel::setPosition(float x, float y)
{
  _background->setPosition(x, y);

  const auto bg_pos = _background->getPosition();
  _face->setPosition(bg_pos.x, bg_pos.y - FACE_HEIGHT);

  const std::vector<std::pair<SpriteSP, TextSP>> attributes = {
    std::make_pair(_strengh_icon, _strengh),
    std::make_pair(_endurance_icon, _endurance),
    std::make_pair(_agility_icon, _agility),
    std::make_pair(_intellect_icon, _intellect)
  };

  constexpr float offset_raise = 60;
  const float start_x = bg_pos.x + PADDING;
  float start_y = bg_pos.y + PADDING;
  float offset = 0;

  for(auto& attribute : attributes)
  {
    attribute.first->setPosition(start_x + offset, start_y);
    attribute.second->setPosition(start_x + offset + ICON_WIDTH, start_y);
    offset += offset_raise;
  }

  start_y += ICON_HEIGHT + 5;
  offset = 0;
  const std::vector<std::pair<SpriteSP, TextSP>> resists = {
    std::make_pair(_fire_icon, _fire),
    std::make_pair(_ice_icon, _ice),
    std::make_pair(_wind_icon, _wind),
    std::make_pair(_hearth_icon, _hearth)
  };

  for(auto& resist : resists)
  {
    resist.first->setPosition(start_x + offset, start_y);
    resist.second->setPosition(start_x + offset + ICON_WIDTH, start_y);
    offset += offset_raise;
  }
}

void CombatCharacterPanel::unfocus(bool force)
{
  if(!force && _focused_character)
    setCharacter(_focused_character, false);
  else
    hide();

  if(force)
    _focused_character.reset();
}

}
