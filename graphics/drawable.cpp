#include "drawable.hpp"

namespace graphics {

void Drawable::draw(sf::RenderTarget& target, sf::RenderStates states) const noexcept
{
  if(_visible)
    internalDraw(target, states);
}

void Drawable::update(const sf::Time& time)
{
  for(auto& animation : _animations)
    animation->update(time);

  // Removed finished animations
  _animations.erase(std::remove_if(_animations.begin(), _animations.end(), [](const AnimationSP& animation){
    return animation->isFinished();
  }), _animations.end());
}

void Drawable::removeAnimation(AnimationSP target_animation)
{
  _animations.erase(std::remove_if(_animations.begin(), _animations.end(), [&](const AnimationSP& animation){
    return animation == target_animation;
  }), _animations.end());
}

}
