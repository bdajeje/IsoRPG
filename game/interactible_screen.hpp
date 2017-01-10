#ifndef INTERACTIBLESCREEN_HPP
#define INTERACTIBLESCREEN_HPP

#include "graphics/drawable.hpp"
#include "graphics/screen.hpp"
#include "graphics/sprite.hpp"
#include "game/events/handler.hpp"

namespace game {

class InteractibleScreen : public graphics::Screen,
                           public events::Handler
{
  struct HoverFuncs
  {
    HoverFuncs(std::function<void()> focus, std::function<void()> unfocus)
      : _focus {focus}
      , _unfocus {unfocus}
    {}

    std::function<void()> _focus;
    std::function<void()> _unfocus;
  };

  public:

    virtual ~InteractibleScreen() = default;

    virtual void update(const sf::Time& time) override;
    virtual events::EventAction handleEvents(const sf::Event& event) override;

    /*! Called every time the screen is shown on top of others */
    virtual void show() {}

  protected:

    void addClickable(graphics::DrawableSP clickable, std::function<void()> func);
    void addHoverable(graphics::DrawableSP hoverable, std::function<void()> focus, std::function<void()> unfocus);
    graphics::DrawableSP hovered(int x, int y) const noexcept;
    bool clicked(int x, int y) const noexcept;

  private:

    std::map<graphics::DrawableSP, std::function<void()>> _clickables;
    std::map<graphics::DrawableSP, HoverFuncs> _hoverables;
    graphics::DrawableSP _current_hover;
};

using InteractibleScreenSP = std::shared_ptr<InteractibleScreen>;

}

#endif // INTERACTIBLESCREEN_HPP
