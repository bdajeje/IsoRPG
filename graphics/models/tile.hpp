#ifndef TILE_HPP
#define TILE_HPP

#include <SFML/Graphics.hpp>
#include "graphics/drawable.hpp"
#include "game/transformable.hpp"
#include "graphics/sprite.hpp"

namespace graphics {

class Tile : public Drawable
           , public game::Transformable
{
  public:

    enum class Direction {
      Left, Right, Top, Bottom
    };

    Tile(sf::Vector2f point_1, sf::Vector2f point_2, sf::Vector2f point_3, sf::Vector2f point_4, const std::string& filename);

    void select();
    void unselect();

    void hover();
    void unhover();

    void setMovementAllowed(bool value);
    void setHighlighted();
    void resetLines();
    void resetFillColor();

    void setBlocking(bool value) { _blocking = value; }

    sf::FloatRect getGlobalBounds() const { return _sprite->getGlobalBounds(); }
    const sf::Vector2f& getPosition() const override { return _point_1; }

    std::shared_ptr<sf::ConvexShape>& shape() noexcept { return _shape; }
    bool blocking() const { return _blocking; }
    void toggleShowGrid() noexcept;

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
};

using ShapeSP = std::shared_ptr<sf::Shape>;
using TileSP = std::shared_ptr<Tile>;

}

#endif // TILE_HPP
