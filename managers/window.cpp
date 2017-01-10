#include "window.hpp"
#include "utils/settings.hpp"

namespace mgr {

std::unique_ptr<Window> Window::_instance;

std::unique_ptr<Window>& Window::init(const sf::String &title, sf::Uint32 style, const sf::ContextSettings &settings)
{
  _instance.reset(new Window{title, style, settings});
  return _instance;
}

Window::Window(const sf::String& title, sf::Uint32 style, const sf::ContextSettings& settings)
   : sf::RenderWindow{{utils::Settings::instance()->get<unsigned int>("window_width", 1000),
                      utils::Settings::instance()->get<unsigned int>("window_height", 1000)},
                      title, style, settings}
{
}

}
