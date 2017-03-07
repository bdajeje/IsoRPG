#include "scrollable_container.hpp"
#include "managers/texture_manager.hpp"
#include "utils/graphics.hpp"

namespace graphics {

using namespace game::events;

namespace {
  const float SCROLL_BAR_WIDTH = 20;
//  const float SCROLL_BAR_WIDTH_X_PADDING = 5;
}

ScrollableContainer::ScrollableContainer(int width, int height, const sf::Vector2f& pos)
  : Container {width, height, pos}
{
  _sprite = std::make_shared<Sprite>(width, height);
  _transformable = _sprite->transformable();

  Transformable::setPosition(pos);
}

void ScrollableContainer::internalDraw(sf::RenderTarget& target, sf::RenderStates states) const noexcept
{
  _sprite->draw(target, states);
  if(_scroll_bar)
    _scroll_bar->draw(target, states);
}

void ScrollableContainer::updateTexture()
{
//  utils::graphics::resize(_sprite, _width, totalHeight());
  _render_texture.create(_width, totalHeight());
  _render_texture.clear(sf::Color::Red);
  _background->draw(_render_texture);

  for(const DrawableSP& drawable : _drawables)
    drawable->draw(_render_texture);

  const sf::Texture& texture = _render_texture.getTexture();
  sf::Image image = texture.copyToImage();
  image.flipVertically();
  _texture.loadFromImage(image);
  _sprite->setTexture(_texture);
//  moveView(0);
}

void ScrollableContainer::addDrawable(DrawableSP drawable, const sf::Vector2f& pos)
{
  drawable->setPosition(pos);
  _drawables.push_back(drawable);

  const auto& bounds = getGlobalBounds();

  if(!_scroll_bar)
  {
    const auto& pos = getPosition();
    _scroll_bar = std::make_shared<Rectangle>(SCROLL_BAR_WIDTH, 1, sf::Color::White);
    _scroll_bar->setPosition(pos.x + bounds.width - SCROLL_BAR_WIDTH, pos.y);
  }

  // Update scoll bar height
  const float height = bounds.height * (bounds.height / totalHeight());
  _scroll_bar->shape()->setSize(sf::Vector2f{SCROLL_BAR_WIDTH, height});
}

void ScrollableContainer::moveScrollBar(int y)
{
  const int target_pos = y - _mouse_y_scroll_bar_offset;
  const auto& ScrollableContainer_pos = getPosition();

  if(target_pos < ScrollableContainer_pos.y)
    return;
  else if(target_pos + _scroll_bar->getGlobalBounds().height > ScrollableContainer_pos.y + getGlobalBounds().height)
    return;

  _scroll_bar->setPosition(_scroll_bar->getPosition().x, target_pos);

  const float y_limit = getGlobalBounds().height - _scroll_bar->getGlobalBounds().height;
  moveView(y * 100 / y_limit);
}

void ScrollableContainer::moveView(float percentage)
{ return;
  if(percentage > 100)
    percentage = 100;
  if(percentage < 0)
    percentage = 0;

  const float y = totalHeight() * percentage / 100;
  auto rect = _sprite->getTextureRect();
  rect.height = y;
  _sprite->setTextureRect(rect);
}

float ScrollableContainer::totalHeight() const noexcept
{
  const auto& last_drawable = _drawables.back();
  return last_drawable->getPosition().y + last_drawable->getGlobalBounds().height;
}

EventAction ScrollableContainer::handleEvents(const sf::Event& event)
{
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wswitch"
  switch(event.type)
  {
    case sf::Event::MouseButtonPressed:
    {
      // If scroll bar is clicked, set scrolling mode
      if(_scroll_bar && _scroll_bar->getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
      {
        _scrolling = true;
        _mouse_y_scroll_bar_offset = event.mouseButton.y - _scroll_bar->getPosition().y;
        _scroll_bar->setColor(sf::Color{100, 100, 100});
      }

      break;
    }
    case sf::Event::MouseMoved:
    {
      if(_scrolling)
        moveScrollBar(event.mouseMove.y);
      else if(_scroll_bar)
      {
        if(_scroll_bar->getGlobalBounds().contains(event.mouseMove.x, event.mouseMove.y))
          _scroll_bar->setColor(sf::Color{150, 150, 150});
        else
          _scroll_bar->setColor(sf::Color::White);
      }

      break;
    }
    case sf::Event::MouseButtonReleased:
    {
      if(_scrolling)
      {
        _scrolling = false;
        if(_scroll_bar->getGlobalBounds().contains(event.mouseMove.x, event.mouseMove.y))
          _scroll_bar->setColor(sf::Color{150, 150, 150});
        else
          _scroll_bar->setColor(sf::Color::White);
      }
      break;
    }
  }
#pragma GCC diagnostic pop

  return EventAction::Continue;
}

void ScrollableContainer::move(float x, float y)
{
  Container::move(x, y);
  _sprite->move(x, y);
}

}
