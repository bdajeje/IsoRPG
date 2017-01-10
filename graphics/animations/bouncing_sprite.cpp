#include "bouncing_sprite.hpp"
#include "graphics/sprite.hpp"

namespace graphics {
namespace animations {

BouncingSprite::BouncingSprite(std::shared_ptr<Sprite>& sprite, float x_bounce, float y_bounce, const sf::Time& time)
  : SpriteAnimation{sprite}
  , _x_bounce {x_bounce}
  , _y_bounce {y_bounce}
  , _time {time.asMilliseconds()}
  , _original_pos {sprite->getPosition()}
{
  if(_x_bounce == 0 && _y_bounce == 0)
    _finished = true;
}

void BouncingSprite::update(const sf::Time& elapsed_time)
{
  if(isFinished())
    return;

  if(_elapsed_time + elapsed_time.asMilliseconds() > _time)
  {
    _elapsed_time = _elapsed_time + elapsed_time.asMilliseconds() - _time;
    _forward = !_forward;
  }
  else
    _elapsed_time += elapsed_time.asMilliseconds();

  auto updatePos = [&](float original, float bounce) -> float {
    if(_forward)
      return original + (_elapsed_time * bounce / _time) - (bounce / 2);
    else
      return original + bounce - (_elapsed_time * bounce / _time) - (bounce / 2);
  };

  sf::Vector2f pos;
  pos.x = updatePos(_original_pos.x, _x_bounce);
  pos.y = updatePos(_original_pos.y, _y_bounce);

  _sprite->setPosition(pos);
}

}
}
