#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <memory>
#include <SFML/Graphics.hpp>

namespace mgr {

class Window : public sf::RenderWindow
{
  public:

    static std::unique_ptr<Window>& init(const sf::String& title, sf::Uint32 style = sf::Style::Default, const sf::ContextSettings& settings = sf::ContextSettings());
    static std::unique_ptr<Window>& instance() { return _instance; }
    static unsigned int width() { return _instance->getSize().x; }
    static unsigned int height() { return _instance->getSize().y; }

  private:

    Window(const sf::String& title, sf::Uint32 style, const sf::ContextSettings& settings);

  private:

    static std::unique_ptr<Window> _instance;
};

}

#endif // WINDOW_HPP
