#include "delay.hpp"

namespace graphics {
namespace animations {

Delay::Delay(AnimationSP animation, const sf::Time& delay)
  : _animation {animation}
  , _delay {delay}
{

}

void Delay::update(const sf::Time& time)
{
  if(isFinished())
    return;

  if(_delay <= sf::Time::Zero)
  {
    _animation->update(time);
    if(_animation->isFinished())
      _finished = true;
  }
  else
    _delay -= time;
}

}
}
