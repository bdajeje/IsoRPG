#include "text_appearance.hpp"

#include <iostream>

namespace graphics {
namespace animations {

TextAppearance::TextAppearance(TextSP& text, const sf::Time& time)
  : TextAnimation {text}
  , _original_text {text->getString()}
  , _time {time.asMilliseconds()}
{
  _text->setString("");
}

void TextAppearance::update(const sf::Time& elapsed_time)
{
  if(isFinished())
    return;

  _elapsed_time += elapsed_time.asMilliseconds();
  const uint nbr_shown_characters = _original_text.getSize() * _elapsed_time / _time;

  _text->setString(_original_text.substring(0, nbr_shown_characters));
  _text->show();

  if(_elapsed_time >= _time)
    _finished = true;
}

void TextAppearance::finish() noexcept
{
  update(sf::milliseconds(_time - _elapsed_time));
}

}
}
