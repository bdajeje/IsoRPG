#ifndef ScrollableContainer_HPP
#define ScrollableContainer_HPP

#include <SFML/Graphics.hpp>

#include "graphics/models/container.hpp"
#include "game/events/handler.hpp"

namespace graphics {

class ScrollableContainer final : public Container
                                , public game::events::Handler
{
  public:

    ScrollableContainer(int width, int height, const sf::Vector2f& pos);

    void addDrawable(DrawableSP drawable, const sf::Vector2f& pos);
    virtual game::events::EventAction handleEvents(const sf::Event& event) override;
    float totalHeight() const noexcept;
    void updateTexture();
    void move(float x, float y);

  protected:

    virtual void internalDraw(sf::RenderTarget& target, sf::RenderStates states) const noexcept;
    void moveScrollBar(int y);
    void moveView(float percentage);

  protected:

    SpriteSP _sprite;
    sf::RenderTexture _render_texture;
    sf::Texture _texture;
    RectangleSP _scroll_bar;
    int _mouse_y_scroll_bar_offset {0};
    bool _scroll {true};
    bool _scrolling {false};
};

using ScrollableContainerSP = std::shared_ptr<ScrollableContainer>;

}

#endif // ScrollableContainer_HPP
