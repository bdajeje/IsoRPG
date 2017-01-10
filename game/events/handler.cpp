#include "handler.hpp"

namespace game {
namespace events {

bool Handler::isKeyAllowed(sf::Keyboard::Key key, utils::KeyLimitor& limitor) noexcept
{
  return sf::Keyboard::isKeyPressed(key) && limitor.isAllow(key);
}

}
}
