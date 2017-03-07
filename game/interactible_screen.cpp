#include "interactible_screen.hpp"
#include "graphics/mouse.hpp"

#include <SFML/System.hpp>

namespace game {

void InteractibleScreen::update(const sf::Time& time)
{
  graphics::Screen::update(time);
}

void InteractibleScreen::addHoverable(graphics::DrawableSP hoverable)
{
  _hoverables.emplace(hoverable, HoverFuncs{});
}

void InteractibleScreen::addHoverable(graphics::DrawableSP hoverable, std::function<void()> focus, std::function<void()> unfocus)
{
  _hoverables.emplace(hoverable, HoverFuncs{focus, unfocus});
}

void InteractibleScreen::addClickable(graphics::DrawableSP clickable, std::function<void()> func)
{
  _clickables[clickable] = func;
}

void InteractibleScreen::unhoverCurrent()
{
  if(_current_hover)
  {
    _current_hover->unhover();
    auto current_hoverable = _hoverables.at(_current_hover);
    if(current_hoverable._unfocus)
      current_hoverable._unfocus();
    _current_hover.reset();
    graphics::Mouse::setStatus(graphics::Mouse::Status::Normal);
  }
}

bool InteractibleScreen::hovered(int x, int y) noexcept
{
  // Search for hover
  for(auto it :_hoverables)
  {
    if(it.first->getGlobalBounds().contains(x, y))
    {
      if(!it.first->isVisible())
        continue;

      if(_current_hover == it.first)
        return true;

      it.first->hover();
      if(it.second._focus)
        it.second._focus();
      graphics::Mouse::setStatus(graphics::Mouse::Status::Hover);
      unhoverCurrent();
      _current_hover = it.first;
      return true;
    }
  }

  // No hover found
  unhoverCurrent();

  return false;
}

bool InteractibleScreen::clicked(int x, int y) const noexcept
{
  for(const auto it :_clickables)
  {
    auto& clickable = it.first;
    if(clickable->isVisible() && clickable->getGlobalBounds().contains(x, y))
    {
      it.first->clicked(x, y);
      it.second();
      return true;
    }
  }

  return false;
}

events::EventAction InteractibleScreen::handleEvents(const sf::Event& event)
{
  // Call all events handler
  for(auto& hander : _event_handlers)
  {
    const events::EventAction action = hander->handleEvents(event);
    if(action != events::EventAction::Continue)
      return action;
  }

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
      if(hovered(event.mouseMove.x, event.mouseMove.y))
        return events::EventAction::Stop;

      break;
    }
    case sf::Event::MouseButtonReleased:
    {
      if(event.mouseButton.button == sf::Mouse::Button::Left)
      {
        if(clicked(event.mouseButton.x, event.mouseButton.y))
          return events::EventAction::Stop;
      }

      break;
    }
  }
#pragma GCC diagnostic pop

  return events::EventAction::Continue;
}

}
