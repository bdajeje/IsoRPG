#ifndef HANDLER_HPP
#define HANDLER_HPP

#include <SFML/Window/Event.hpp>
#include "utils/key_limitor.hpp"

namespace game {
namespace events {

enum class EventAction {
  Continue,
  Stop,
  ExitScreen,
  Exit
};

class Handler
{
  public:

    virtual ~Handler() = default;

    virtual EventAction handleEvents(const sf::Event& event) = 0;

  protected:

    static bool isKeyAllowed(sf::Keyboard::Key key, utils::KeyLimitor& limitor) noexcept;
};

}
}

#endif // HANDLER_HPP
