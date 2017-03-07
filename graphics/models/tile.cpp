#include "tile.hpp"

#include <assert.h>
#include <iostream>

#include "utils/file.hpp"
#include "utils/json.hpp"
#include "graphics/animations/fill_color.hpp"
#include "graphics/animations/delay.hpp"
#include "graphics/animations/animated_sprite.hpp"

namespace graphics {

namespace {
  constexpr float TILE_WIDTH = 110;
  constexpr float TILE_HEIGHT = 79;
}

Tile::Tile(sf::Vector2f point_1, sf::Vector2f point_2, sf::Vector2f point_3, sf::Vector2f point_4, const std::string& filename)
  : _shape {std::make_shared<sf::ConvexShape>()}
{ 
  _transformable = _shape;

  _shape->setPointCount(4);
  _shape->setPoint(0, point_1);
  _shape->setPoint(1, point_2);
  _shape->setPoint(2, point_3);
  _shape->setPoint(3, point_4);
  _point_1 = point_1;

  const auto data = json::parse(utils::files::read(filename));

  // Create sprite  
  const std::string sprite_file = data["file"];
  if(data["type"] == "animation")
  {
    _sprite = std::make_shared<Sprite>(TILE_WIDTH, TILE_HEIGHT);
    _sprite->addAnimation(std::make_shared<animations::AnimatedSprite>(_sprite, data));
  }
  else
    _sprite = getSprite(sprite_file, TILE_WIDTH, TILE_HEIGHT);

  _sprite->setOrigin(_sprite->getLocalBounds().width / 2, 0);
  _sprite->setPosition(point_1);
  _blocking = data["blocking"];

  unselect();
}

void Tile::internalDraw(sf::RenderTarget& target, sf::RenderStates states) const noexcept
{
  _sprite->draw(target, states);

  if(_show_grid)
    target.draw(*_shape, states);
}

void Tile::select()
{
  updateShape(sf::Color{255, 0, 0}, sf::Color{100, 100, 100, 150}, 1);
}

void Tile::unselect()
{
  resetFillColor();
  resetLines();
}

void Tile::hover(bool force)
{
  _shape->setOutlineThickness(2);
  _shape->setOutlineColor(sf::Color{0, 255, 0});

  if(force)
    _show_grid = true;
}

void Tile::unhover()
{
  _shape->setOutlineThickness(1);
  _shape->setOutlineColor(sf::Color{100, 100, 100, 150});

  if(!_highlighted)
    _show_grid = false;
}

void Tile::setHighlighted(const sf::Color& color, int delay)
{
  cancelAnimations();
  AnimationSP enlight_animation = std::make_shared<animations::FillColor>(_shape, color, sf::milliseconds(400));

  if(delay > 0)
    addAnimation(std::make_shared<animations::Delay>(enlight_animation, sf::milliseconds(delay)));
  else
    addAnimation(enlight_animation);

  _highlighted = true;
  _show_grid = true;
}

void Tile::unHighlight(/*bool animate*/)
{
  const sf::Color color(255, 255, 255, 0);

//  if(animate)
  cancelAnimations();
    addAnimation(std::make_shared<animations::FillColor>(_shape, color, sf::milliseconds(100)));
//  else
//    _shape->setFillColor(color);

  _highlighted = false;
}

void Tile::setMovementAllowed(bool value)
{
  const auto color = value ? sf::Color{0, 255, 0, 255} : sf::Color{255, 0, 0, 255};
  _shape->setOutlineThickness(2);
  _shape->setOutlineColor(color);
  _show_grid = true;
}

void Tile::resetLines()
{
  _shape->setOutlineThickness(1);
  _shape->setOutlineColor(sf::Color{100, 100, 100, 150});
}

void Tile::resetFillColor()
{
  _shape->setFillColor(sf::Color{0, 0, 0, 0});
}

void Tile::updateShape(sf::Color fill_color, sf::Color outline_color, float thickness)
{
  _shape->setFillColor(fill_color);
  _shape->setOutlineThickness(thickness);
  _shape->setOutlineColor(outline_color);
}

void Tile::toggleShowGrid() noexcept
{
  _show_grid = !_show_grid;
}

void Tile::update(const sf::Time& time)
{
  Drawable::update(time);
  _sprite->update(time);
}

}
