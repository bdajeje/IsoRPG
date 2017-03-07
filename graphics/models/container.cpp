#include "container.hpp"
#include "utils/graphics.hpp"

namespace graphics {

Container::Container(int width, int height, const sf::Vector2f& pos, ContainerProps props)
  : _width {width}
  , _height {height}
{
//  if(default_background)
//    setBackground(texture::TextureManager::get("container.png"));

  _background = std::make_shared<Rectangle>(_width, _height, props.bg_color);
  _background->setPosition(pos);
  _transformable = _background->shape();
}

void Container::internalDraw(sf::RenderTarget& target, sf::RenderStates states) const noexcept
{
  _background->draw(target, states);

  for(const DrawableSP& drawable : _drawables)
    drawable->draw(target, states);
}

void Container::addDrawable(DrawableSP drawable, const sf::Vector2f& pos)
{
  drawable->setPosition(getPosition() + pos);
  _drawables.push_back(drawable);  
}

void Container::setPosition(float x, float y)
{
  auto pos = getPosition();
  _background->setPosition(x, y);
  moveElements(x - pos.x , y - pos.y);
}

void Container::move(float x, float y)
{
  _background->move(x, y);

  for(auto& drawable : _drawables)
    drawable->move(x, y);
}

void Container::moveElements(float x, float y)
{
  for(auto& drawable : _drawables)
    drawable->move(x, y);
}

void Container::clicked(int x, int y)
{
  for(const DrawableSP& drawable : _drawables)
  {
    if(drawable->isVisible() && drawable->getGlobalBounds().contains(x, y))
    {
      drawable->clicked(x, y);
      return;
    }
  }
}

//void Container::setBackground(/*const sf::Texture& texture*/)
//{
////  _background = getSprite(texture, _width, _height);
//  _background = std::make_shared<Rectangle>(_width, _height);
//}

}
