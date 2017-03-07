#ifndef TILE_HPP
#define TILE_HPP

#include <SFML/Graphics.hpp>
#include "graphics/drawable.hpp"
#include "graphics/sprite.hpp"

namespace graphics {

class Tile : public Drawable           
{
  public:

    enum class Direction {
      Left, Right, Top, Bottom
    };

    Tile(sf::Vector2f point_1, sf::Vector2f point_2, sf::Vector2f point_3, sf::Vector2f point_4, const std::string& filename);

    void select();
    void unselect();

    void hover(bool force = false);
    void unhover();

    void setMovementAllowed(bool value);
    void setHighlighted(const sf::Color& color = sf::Color{255, 255, 255, 100}, int delay = 0);
    void unHighlight();
    void resetLines();
    void resetFillColor();
    bool isHighlighted() const noexcept { return _highlighted; }

    void setBlocking(bool value) { _blocking = value; }

    sf::FloatRect getGlobalBounds() const { return _sprite->getGlobalBounds(); }
    virtual const sf::Vector2f& getPosition() const override { return _point_1; }

    std::shared_ptr<sf::ConvexShape>& shape() noexcept { return _shape; }
    bool blocking() const { return _blocking; }
    void toggleShowGrid() noexcept;
    void showGrid() noexcept { _show_grid = true; }
    void hideGrid() noexcept { _show_grid = false; }

    virtual void update(const sf::Time& time) override;

    virtual void setColor(const sf::Color& /*color*/) override {}
    virtual const sf::Color getColor() const override { return {}; }

  protected:

    virtual void internalDraw(sf::RenderTarget& target, sf::RenderStates states) const noexcept;
    void updateShape(sf::Color fill_color, sf::Color outline_color, float thickness);

  private:

    std::shared_ptr<sf::ConvexShape> _shape;
    SpriteSP _sprite;
    sf::Vector2f _point_1;
    sf::Color _fill_color;
    bool _blocking;
    bool _show_grid {false};
    bool _highlighted {false};
};

using ShapeSP = std::shared_ptr<sf::Shape>;
using TileSP = std::shared_ptr<Tile>;

}

#endif // TILE_HPP
