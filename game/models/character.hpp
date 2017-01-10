#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <string>
#include <memory>
#include <vector>

#include "utils/maxed_value.hpp"
#include "utils/serializable.hpp"
#include "game/models/character_trait.hpp"
#include "game/models/map_pos.hpp"
#include "game/models/portable_item.hpp"
#include "game/models/inventory_model.hpp"
#include "graphics/animation.hpp"
#include "graphics/animations/animated_sprite.hpp"
#include "graphics/sprite.hpp"

namespace game {

class Character : public graphics::Drawable
                , public utils::Serializable
{
  public:

    Character(const json& data);

    const std::string name() const noexcept { return _name; }
    short level() const noexcept { return _level; }
    uint life() const noexcept { return _life._value; }
    uint maxLife() const noexcept { return _life._max; }
    uint mana() const noexcept { return _mana._value; }
    uint maxMana() const noexcept { return _mana._max; }        
    uint energy() const noexcept { return _energy._value; }
    uint maxEnergy() const noexcept { return _energy._max; }
    int speed() const noexcept { return _speed; }
    bool isAlly() const noexcept { return _ally; }
    InventoryModelSP& inventory() { return _inventory_model; }

    const std::string& traitName(size_t trait_nbr) const noexcept;
    const std::string& faceTextureName() const noexcept { return _face_texture_name; }        

    bool isMoving() { return _moving_animation != nullptr && !_moving_animation->isFinished(); }
    void moveTo(const MapPos& target_map_pos, sf::Vector2f pixel_map_pos);
    const MapPos& mapPos() { return _map_pos; }
    void setMapPos(const MapPos& map_pos) { _map_pos = map_pos; }

    virtual void update(const sf::Time& time) override;
    virtual sf::FloatRect getGlobalBounds() const override { return _sprite->getGlobalBounds(); }
    virtual json save() override;
    graphics::SpriteSP& sprite() { return _sprite; }

    virtual void setColor(const sf::Color& color) override { _sprite->setColor(color); }
    virtual const sf::Color getColor() const override { return _sprite->getColor(); }

  protected:

    virtual void internalDraw(sf::RenderTarget& target, sf::RenderStates states) const noexcept override;

  protected:

    std::string _name;
    std::string _face_texture_name;    
    MaxedValue<uint> _life;
    MaxedValue<uint> _mana;
    MaxedValue<uint> _energy;    
    CharacterTraitSP _trait_1;
    CharacterTraitSP _trait_2;
    short _level;    
    int _speed;
    MapPos _map_pos;
    graphics::AnimationSP _moving_animation;
    graphics::SpriteSP _sprite;
    uint _moving_animation_time;
    InventoryModelSP _inventory_model;
    bool _ally;
    std::map<Direction, graphics::animations::AnimatedSpriteSP> _moves_animations;
    graphics::animations::AnimatedSpriteSP _current_move_animation;
};

using CharacterSP = std::shared_ptr<Character>;

}

#endif // CHARACTER_HPP
