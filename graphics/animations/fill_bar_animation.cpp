#include "fill_bar_animation.hpp"
#include "utils/time.hpp"

namespace graphics {
namespace animations {

FillBarAnimation::FillBarAnimation(FillBarSP fill_bar, int to_value, const sf::Time& time)
  : _fill_bar {fill_bar}
  , _original {fill_bar->value()}
  , _target {to_value}
  , _time {time.asMilliseconds()}
{

}

void FillBarAnimation::update(const sf::Time& elapsed_time)
{
  if(isFinished())
    return;

  _elapsed_time += elapsed_time.asMilliseconds();
  if(_elapsed_time >= _time)
  {
    _elapsed_time = _time;
    _finished = true;
  }

  int value = utils::addTimeDiff(_original, _target, _elapsed_time, _time);
  _fill_bar->setValue(value);
}

}
}
