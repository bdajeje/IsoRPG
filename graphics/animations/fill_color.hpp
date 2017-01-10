#ifndef FILLCOLOR_HPP
#define FILLCOLOR_HPP

#include <SFML/System/Time.hpp>

#include "graphics/animation.hpp"
#include "graphics/models/tile.hpp"

namespace graphics {
namespace animations {

class FillColor final : public Animation
{
  public:

    FillColor(ShapeSP shape, const sf::Color& color, const sf::Time& time);

    virtual void update(const sf::Time& time) override;

  private:

    ShapeSP _shape;
    const sf::Color _original;
    const sf::Color _target;
    int _time;
    int _elapsed_time {0};
};

}
}

#endif // FILLCOLOR_HPP
