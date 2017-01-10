#include "move.hpp"
#include "graphics/sprite.hpp"

namespace graphics {
namespace animations {

Move::Move(SpriteSP sprite, float x, float y, sf::Time time)
  : SpriteAnimation {sprite}
  , _time {time.asMilliseconds()}
{  
  const sf::Int32 total_ms = time.asMilliseconds();
  if(total_ms == 0)
    _finished = true;
  else
  {
    _x_per_ms = x / total_ms;
    _y_per_ms = y / total_ms;
  }
}

void Move::update(const sf::Time& elapsed_time)
{
  if(_finished)
    return;

  uint elapsed_time_ms = elapsed_time.asMilliseconds();
  if(_elapsed_time + elapsed_time_ms >= _time)
  {
    elapsed_time_ms = _time - _elapsed_time;
    _finished = true;
  }
  else
  {
    _elapsed_time += elapsed_time_ms;
  }

  const float x_move = elapsed_time_ms * _x_per_ms;
  const float y_move = elapsed_time_ms * _y_per_ms;

  _sprite->move(x_move, y_move);
}

}
}
