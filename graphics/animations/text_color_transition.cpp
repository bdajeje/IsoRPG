#include "text_color_transition.hpp"
#include "utils/time.hpp"

namespace graphics {
namespace animations {

TextColorTransition::TextColorTransition(TextSP& text, const sf::Color& target, const sf::Time& time)
  : TextAnimation {text}
  , _original {text->getColor()}
  , _target {target}
  , _time {time.asMilliseconds()}
{}

void TextColorTransition::update(const sf::Time& elapsed_time)
{
  if(isFinished())
    return;

  _elapsed_time += elapsed_time.asMilliseconds();
  if(_elapsed_time >= _time)
  {
    _elapsed_time = _time;
    _finished = true;
  }

  sf::Color color;

  color.r = utils::addTimeDiff(_original.r, _target.r, _elapsed_time, _time);
  color.g = utils::addTimeDiff(_original.g, _target.g, _elapsed_time, _time);
  color.b = utils::addTimeDiff(_original.b, _target.b, _elapsed_time, _time);
  color.a = utils::addTimeDiff(_original.a, _target.a, _elapsed_time, _time);

  _text->setColor(color);
}

}
}
