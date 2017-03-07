#include "key_limitor.hpp"

namespace utils {

std::shared_ptr<KeyLimitor> KeyLimitor::_instance;

void KeyLimitor::init(sf::Int32 min_elapsed_time)
{
  _instance.reset(new KeyLimitor(min_elapsed_time));
}

KeyLimitor::KeyLimitor(sf::Int32 min_elapsed_time)
  : _min_elapsed_time { min_elapsed_time }
{
  _timer.start();
}

bool KeyLimitor::isAllow( sf::Keyboard::Key key )
{
  const bool is_different_key = (_instance->_last_checked_key != key);
  _instance->_last_checked_key = key;

  if(is_different_key)
    return true;

  if(_instance->_min_elapsed_time <= _instance->_timer.getElapsedTime().asMilliseconds())
  {
    _instance->_timer.restart();
    return true;
  }

  return false;
}

}
