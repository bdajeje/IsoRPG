#include "character.hpp"
#include "utils/file.hpp"
#include "graphics/animations/move.hpp"

namespace game {

using namespace graphics;

Character::Character(const json& data)
{
  _name    = data["name"];
  _life    = {data["life"]["current"], data["life"]["max"]};
  _mana    = {data["mana"]["current"], data["mana"]["max"]};
  _energy  = {data["energy"]["current"], data["energy"]["max"]};
  _level   = data["level"];
  _speed   = data["speed"];
  _trait_1 = CharacterTrait::create(data["traits"][0]);
  _trait_2 = CharacterTrait::create(data["traits"][1]);  
  _ally    = data["ally"];
  _sprite  = std::make_shared<Sprite>(90, 106);
  _moves_animations[Direction::TopLeft] = std::make_shared<graphics::animations::AnimatedSprite>(_sprite, data["sprites"]["movements"]["top_left"]);
  _moves_animations[Direction::TopRight] = std::make_shared<graphics::animations::AnimatedSprite>(_sprite, data["sprites"]["movements"]["top_right"]);
  _moves_animations[Direction::BottomLeft] = std::make_shared<graphics::animations::AnimatedSprite>(_sprite, data["sprites"]["movements"]["bottom_left"]);
  _moves_animations[Direction::BottomRight] = std::make_shared<graphics::animations::AnimatedSprite>(_sprite, data["sprites"]["movements"]["bottom_right"]);

  _face_texture_name = data["sprites"]["face"];
  _moving_animation_time = 200; // \todo attribute specific per character

  if(data.find("pos") != data.end())
  {
    _map_pos.x = data["pos"][0];
    _map_pos.y = data["pos"][1];
  }

  _inventory_model = std::make_shared<InventoryModel>(data);
}

const std::string& Character::traitName(size_t trait_nbr) const noexcept
{
  const CharacterTraitSP& trait = trait_nbr == 0 ? _trait_1 : _trait_2;
  if(trait)
    return trait->name();

  static const std::string empty;
  return empty;
}

void Character::moveTo(const MapPos& target_map_pos, sf::Vector2f pixel_map_pos)
{  
  // Correctly position character sprite
  const sf::FloatRect bounds = _sprite->getGlobalBounds();
  pixel_map_pos.x -= bounds.width / 2;
  pixel_map_pos.y -= bounds.height / 2;

  // Stop previous movement animation
  if(_current_move_animation)
    _sprite->removeAnimation(_current_move_animation);

  // Update sprite movement animation
  _current_move_animation = _moves_animations.at(getDirection(_map_pos, target_map_pos));
  _current_move_animation->setFrameRate(_moving_animation_time / _current_move_animation->steps());
  _current_move_animation->restart();
  _sprite->addAnimation(_current_move_animation);

  // Move animation
  _moving_animation = std::make_shared<animations::Move>(_sprite,
                                                         pixel_map_pos.x - _sprite->getPosition().x,
                                                         pixel_map_pos.y - _sprite->getPosition().y,
                                                         sf::milliseconds(_current_move_animation->animationTime()));
  _sprite->addAnimation(_moving_animation);

  setMapPos(target_map_pos);
}

void Character::update(const sf::Time &time)
{
  _sprite->update(time);
}

void Character::internalDraw(sf::RenderTarget& target, sf::RenderStates states) const noexcept
{
  _sprite->draw(target, states);
}

json Character::save()
{
  json data;

  data["name"] = _name;
  data["level"] = _level;
  data["traits"].push_back(_trait_1->name());
  data["traits"].push_back(_trait_2->name());
  data["sprites"]["face"] = _face_texture_name;
  data["life"]["current"] = _life._value;
  data["life"]["max"] = _life._max;
  data["mana"]["current"] = _mana._value;
  data["mana"]["max"] = _mana._max;
  data["energy"]["current"] = _energy._value;
  data["energy"]["max"] = _energy._max;
  data["inventory"] = _inventory_model->save();
  data["ally"] = isAlly();

  // \todo: can't save animations dude...
//  data["sprites"]["movements"]["top_left"] = _moves_animations[Direction::TopLeft];
//  data["sprites"]["movements"]["top_right"] = _moves_animations[Direction::TopRight];
//  data["sprites"]["movements"]["bottom_left"] = _moves_animations[Direction::BottomLeft];
//  data["sprites"]["movements"]["bottom_right"] = _moves_animations[Direction::BottomRight];

  return data;
}

}
