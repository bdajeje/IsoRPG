#ifndef DRAWABLE_HPP
#define DRAWABLE_HPP

#include <memory>
#include <list>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Color.hpp>

#include "graphics/animation.hpp"
#include "game/transformable.hpp"
#include "game/updatable.hpp"

namespace graphics {

class Drawable : public game::Updatable
               , public game::Transformable
{
  public:

    Drawable() = default;
    virtual ~Drawable() = default;

    void hide() noexcept { _visible = false; }
    void show() noexcept { _visible = true; }
    bool isVisible() const noexcept { return _visible == true; }

    void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const noexcept;
    virtual void update(const sf::Time& time) override;

    virtual sf::FloatRect getGlobalBounds() const = 0;
    virtual void setColor(const sf::Color& color) = 0;
    virtual const sf::Color getColor() const = 0;
    virtual void hover() {}
    virtual void unhover() {}
    virtual void clicked(int /*x*/, int /*y*/) {}

    void addAnimation(AnimationSP animation) { _animations.push_back(animation); }
    void removeAnimation(AnimationSP animation);
    void cancelAnimations() { _animations.clear(); }
    bool hasAnimations() const noexcept { return !_animations.empty(); }

  protected:

    virtual void internalDraw(sf::RenderTarget& target, sf::RenderStates states) const noexcept = 0;

  private:

    bool _visible {true};
    std::list<AnimationSP> _animations;
};

using DrawableSP = std::shared_ptr<Drawable>;

}

#endif // DRAWABLE_HPP
