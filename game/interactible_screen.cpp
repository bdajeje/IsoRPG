#include "interactible_screen.hpp"
#include "graphics/mouse.hpp"

#include <SFML/System.hpp>

namespace game {

void InteractibleScreen::update(const sf::Time& time)
{
  graphics::Screen::update(time);
}

void InteractibleScreen::addHoverable(graphics::DrawableSP hoverable, std::function<void()> focus, std::function<void()> unfocus)
{
  _hoverables.emplace(hoverable, HoverFuncs{focus, unfocus});
}

void InteractibleScreen::addClickable(graphics::DrawableSP clickable, std::function<void()> func)
{
  _clickables[clickable] = func;
}

graphics::DrawableSP InteractibleScreen::hovered(int x, int y) const noexcept
{
  for(const auto it :_hoverables)
  {
    if(it.first->getGlobalBounds().contains(x, y))
    {
      it.second._focus();
      graphics::Mouse::setStatus(graphics::Mouse::Status::Hover);
      return it.first;
    }
  }

  graphics::Mouse::setStatus(graphics::Mouse::Status::Normal);
  return {};
}

bool InteractibleScreen::clicked(int x, int y) const noexcept
{
  for(const auto it :_clickables)
  {
    auto& clickable = it.first;
    if(clickable->isVisible() && clickable->getGlobalBounds().contains(x, y))
    {
      it.second();
      return true;
    }
  }

  return false;
}

events::EventAction InteractibleScreen::handleEvents(const sf::Event& event)
{
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wswitch"
  switch(event.type)
  {
    case sf::Event::KeyPressed:
    {
      // \todo create method registerKey(key, method)

      break;
    }
    case sf::Event::MouseMoved:
    {
      graphics::DrawableSP hover = hovered(event.mouseMove.x, event.mouseMove.y);

      if(_current_hover && hover != _current_hover)
        _hoverables.at(_current_hover)._unfocus();

      _current_hover = hover;

      if(hover)
        return events::EventAction::Stop;

      break;
    }
    case sf::Event::MouseButtonReleased:
    {
      if(clicked(event.mouseButton.x, event.mouseButton.y))
        return events::EventAction::Stop;
      break;
    }
  }
#pragma GCC diagnostic pop

  return events::EventAction::Continue;
}

}
