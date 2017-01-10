#ifndef FILLBARANIMATION_HPP
#define FILLBARANIMATION_HPP

#include "graphics/animation.hpp"
#include "graphics/models/fill_bar.hpp"

namespace graphics {
namespace animations {

class FillBarAnimation final : public Animation
{
  public:

    FillBarAnimation(FillBarSP fill_bar, int to_value, const sf::Time& time);

    virtual void update(const sf::Time& time) override;

  private:

    FillBarSP _fill_bar;
    const int _original;
    const int _target;
    int _time;
    int _elapsed_time {0};
};

}
}

#endif // FILLBARANIMATION_HPP
