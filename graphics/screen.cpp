#include "screen.hpp"

namespace graphics {

void Screen::update(const sf::Time& time)
{
  for(const DrawableSP& drawable : _drawables)
    drawable->update(time);

  // Update animations
  for(AnimationSP& animation : _animations)
    animation->update(time);

  // Removed finished animations
  _animations.erase(std::remove_if(_animations.begin(), _animations.end(), [](const AnimationSP& animation){
    return animation->isFinished();
  }), _animations.end());
}

void Screen::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  if(!_visible)
    return;

  for(const DrawableSP& drawable : _drawables)
    drawable->draw(target, states);
}


}
