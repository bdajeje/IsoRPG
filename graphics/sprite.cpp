#include "sprite.hpp"

#include <SFML/Graphics/RenderTarget.hpp>

#include "managers/texture_manager.hpp"

namespace graphics {

Sprite::Sprite(float width, float height)
  : _sprite {std::make_shared<sf::Sprite>()}
  , _width {width}
  , _height {height}
{
  _transformable = _sprite;
}

void Sprite::internalDraw(sf::RenderTarget& target, sf::RenderStates states) const noexcept
{
  target.draw(*_sprite, states);
}

void Sprite::setTexture(const sf::Texture& texture, bool keep_size)
{  
  _sprite->setTexture(texture, true);

  if(keep_size)
  {
    const auto texture_size = texture.getSize();
    _sprite->setScale( _width / texture_size.x, _height / texture_size.y );
  }
}

void Sprite::setTextureRect(const sf::IntRect& rectangle)
{
//  auto bounds = _sprite->getGlobalBounds();
//  _sprite->setScale( bounds.width / rectangle.width, bounds.height / rectangle.height );
//  _sprite->setScale( 1, 1 );
  _sprite->setTextureRect(rectangle);
}

SpriteSP getSprite(const std::string& texture_file_path, float width, float height)
{
  return getSprite(texture::TextureManager::get(texture_file_path), width, height);
}

SpriteSP getSprite(const sf::Texture& texture, float width, float height)
{
  auto sprite = std::make_shared<Sprite>(width, height);
  sprite->setTexture(texture);
  return sprite;
}

}
