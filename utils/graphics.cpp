#include "utils/graphics.hpp"
#include "game/transformable.hpp"

#include <assert.h>

namespace utils {
namespace graphics{

void centerHonrizontally(sf::Text& text, unsigned int total_width)
{
  const sf::FloatRect bounds = text.getGlobalBounds();
  text.setPosition( (total_width - bounds.width) / 2, text.getPosition().y );
}

void centerVerticalPosition(std::vector<sf::Text>& texts, unsigned int total_width, unsigned int total_height)
{
  if( texts.empty() )
    return;

  const unsigned int y_margin = total_height / (texts.size() + 1);
  const size_t nbr_items = texts.size();
  for(size_t i = 0; i < nbr_items; ++i)
  {
    sf::Text& text = texts.at(i);
    const sf::FloatRect bounds = text.getGlobalBounds();
    text.setPosition( 0, (y_margin * (i+1)) - (bounds.height / 2));
    centerHonrizontally(text, total_width);
  }
}

void centerPosition(sf::Text& text, unsigned int total_width, unsigned int total_height)
{
  const sf::FloatRect bounds = text.getGlobalBounds();
  text.setPosition( (total_width - bounds.width) / 2, (total_height - bounds.height) / 2 );
}

void resize(SpriteSP& sprite, float x, float y)
{
  sprite->setScale( x / sprite->getLocalBounds().width,
                    y / sprite->getLocalBounds().height );
}

void centerHonrizontally(SpriteSP& sprite, uint width)
{
  const sf::FloatRect bounds = sprite->getGlobalBounds();

  sprite->setPosition(
        (width - bounds.width) / 2,
        sprite->getPosition().y
  );
}

void centerHonrizontally(SpriteSP& sprite, const sf::Vector2u& parent_size)
{
  centerHonrizontally(sprite, parent_size.x);
}

}
}
