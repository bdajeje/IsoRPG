#ifndef HANDLER_HPP
#define HANDLER_HPP

#include <SFML/Window/Event.hpp>
#include "utils/key_limitor.hpp"
#include "utils/keybinding.h"

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

    static bool isKeyAllowed(sf::Keyboard::Key key) noexcept;
};

}

using HandlerSP = std::shared_ptr<events::Handler>;

}

#endif // HANDLER_HPP
