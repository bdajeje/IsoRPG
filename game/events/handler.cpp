#include "handler.hpp"

namespace game {
namespace events {

bool Handler::isKeyAllowed(sf::Keyboard::Key key) noexcept
{
  return sf::Keyboard::isKeyPressed(key) && utils::KeyLimitor::isAllow(key);
}

}
}
