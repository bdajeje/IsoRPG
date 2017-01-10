#include "key_limitor.hpp"

namespace utils {

KeyLimitor::KeyLimitor(sf::Int32 min_elapsed_time )
  : _min_elapsed_time { min_elapsed_time }
{
  _timer.start();
}

bool KeyLimitor::isAllow( sf::Keyboard::Key key )
{
  const bool is_different_key = (_last_checked_key != key);
  _last_checked_key = key;

  if( is_different_key )
    return true;

  if( _min_elapsed_time <= _timer.getElapsedTime().asMilliseconds() )
  {
    _timer.restart();
    return true;
  }

  return false;
}

}
