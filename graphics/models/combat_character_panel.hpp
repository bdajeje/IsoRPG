#ifndef COMBATCHARACTERPANEL_HPP
#define COMBATCHARACTERPANEL_HPP

#include "graphics/drawable.hpp"
#include "game/transformable.hpp"

namespace graphics {

class CombatCharacterPanel final : public Drawable
                                 , public game::Transformable
{
  public:

    CombatCharacterPanel(const sf::Vector2f& pos);

    void setPosition(float x, float y) override {}
    void setPosition(const sf::Vector2f& position) override { setPosition(position.x, position.y); }

    virtual sf::FloatRect getGlobalBounds() const override { return {}; }
    virtual void update(const sf::Time& time) override {}

    virtual void setColor(const sf::Color& color) override {}
    virtual const sf::Color getColor() const override {}

  protected:

    virtual void internalDraw(sf::RenderTarget& target, sf::RenderStates states) const noexcept {}

  private:

    sf::Vector2f _pos;
};

using CombatCharacterPanelSP = std::shared_ptr<CombatCharacterPanel>;

}

#endif // COMBATCHARACTERPANEL_HPP
