#ifndef SCREEN_HPP
#define SCREEN_HPP

#include <memory>

#include <SFML/Graphics.hpp>

#include "graphics/animation.hpp"
#include "graphics/drawable.hpp"
#include "game/updatable.hpp"
#include "utils/typedefs.hpp"

namespace graphics {

class Screen : public sf::Drawable,
               public game::Updatable
{
  public:

    virtual ~Screen() = default;

    virtual void update(const sf::Time& time) override;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    void hide() { _visible = false; }
    void show() { _visible = true; }

    bool isVisible() const { return _visible; }
    bool isFinished() const { return _finish; }

  protected:

    void addDrawable(DrawableSP drawable) { _drawables.push_back(drawable); }
    void removeDrawable(DrawableSP drawable);
    void addAnimation(AnimationSP animation) { _animations.push_back(animation); }

  protected:

    std::vector<DrawableSP> _drawables;
    std::vector<AnimationSP> _animations;

  private:

    bool _visible {true};

  protected:

    bool _finish {false};
};

using ScreenSP = std::shared_ptr<Screen>;

}

#endif // SCREEN_HPP
