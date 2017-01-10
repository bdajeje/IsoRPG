#ifndef UTILS_GRAPHICS_HPP
#define UTILS_GRAPHICS_HPP

#include <SFML/Graphics.hpp>
#include "graphics/text.hpp"
#include "graphics/sprite.hpp"

using namespace graphics;

namespace utils {
namespace graphics{

/*! Horizontally and Vertically center a text */
void centerPosition(sf::Text& text, unsigned int total_width, unsigned int total_height);

/*! Horizontally center a text */
void centerHonrizontally(sf::Text& text, unsigned int total_width);

/*! Vertically align a list of texts (usefull to place menu items)
 *  Also centers texts horizontally
 */
void centerVerticalPosition(std::vector<sf::Text>& texts, unsigned int total_width, unsigned int total_height);

/*! Resize a sprite */
void resize(SpriteSP& sprite, float x, float y);

void centerHonrizontally(SpriteSP& sprite, const sf::Vector2u& parent_size);
void centerHonrizontally(SpriteSP& sprite, uint width);

template <class T>
void vAlign(std::vector<std::shared_ptr<T>>& transformables, float x, float y_from, float total_height)
{
  if(transformables.empty())
    return;

  const float padding = total_height / transformables.size();

  for(std::shared_ptr<T>& transformable : transformables)
  {
    transformable->setPosition(x, y_from);
    y_from += padding;
  }
}

template <class T>
void hCircleAlign(std::vector<std::shared_ptr<T>>& transformables, float max_x_offset)
{
  if(transformables.empty() || max_x_offset == 0)
    return;

  for(size_t i = 0, nbr = transformables.size() / 2; i < nbr; ++i)
  {
    const float x = max_x_offset - max_x_offset * (static_cast<float>(i) / static_cast<float>(nbr));
    transformables[i]->move(x, 0);
  }

  for(size_t i = 0, nbr = transformables.size() / 2; i < nbr; ++i)
  {
    const float x = max_x_offset * (static_cast<float>(i) / static_cast<float>(nbr));
    transformables[i + nbr]->move(x, 0);
  }
}

}
}

#endif // UTILS_GRAPHICS_HPP

