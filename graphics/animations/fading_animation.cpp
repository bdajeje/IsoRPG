#include "fading_animation.hpp"

namespace graphics {
namespace animations {

FadingAnimation::FadingAnimation(DrawableSP drawable, const sf::Time& time, Type type, bool start)
  : _drawable {drawable}
  , _time {time.asMilliseconds()}
  , _type {type}
  , _started {start}
{}

void FadingAnimation::start() noexcept
{
  _started = true;
  update(sf::milliseconds(0));
  _drawable->show();
}

void FadingAnimation::update(const sf::Time& elapsed_time)
{
  if(!_started || isFinished())
    return;

  _elapsed_time += elapsed_time.asMilliseconds();

  if(_elapsed_time >= _time)
  {
    _elapsed_time = _time;
    _finished = true;
  }

  sf::Color color = _drawable->getColor();

  if(_type == Type::In)
    color.a = _elapsed_time * 255 / _time;
  else
    color.a = 255 - ((_elapsed_time * 255) / _time);

  _drawable->setColor(color);
  _drawable->show();
}

}
}
