#ifndef COMBATCHARACTERPANEL_HPP
#define COMBATCHARACTERPANEL_HPP

#include "graphics/drawable.hpp"
#include "graphics/sprite.hpp"
#include "graphics/text.hpp"
#include "game/models/ennemy_character.hpp"

namespace graphics {

class CombatCharacterPanel final : public Drawable
{
  public:

    CombatCharacterPanel(const sf::Vector2f& pos);

    virtual void setPosition(float x, float y) override;

    virtual sf::FloatRect getGlobalBounds() const override { return {}; }
    virtual void update(const sf::Time& /*time*/) override {}

    virtual void setColor(const sf::Color& /*color*/) override {}
    virtual const sf::Color getColor() const override { return {}; }

    void setCharacter(game::CharacterSP character, bool stay_focused);
    void unfocus(bool force);

  protected:

    virtual void internalDraw(sf::RenderTarget& target, sf::RenderStates states) const noexcept;

  private:

    SpriteSP _background;
    SpriteSP _face;
    TextSP _strengh;
    TextSP _endurance;
    TextSP _agility;
    TextSP _intellect;
    TextSP _fire;
    TextSP _ice;
    TextSP _wind;
    TextSP _hearth;
    SpriteSP _strengh_icon;
    SpriteSP _endurance_icon;
    SpriteSP _agility_icon;
    SpriteSP _intellect_icon;
    SpriteSP _fire_icon;
    SpriteSP _ice_icon;
    SpriteSP _wind_icon;
    SpriteSP _hearth_icon;
    game::CharacterSP _focused_character;
};

using CombatCharacterPanelSP = std::shared_ptr<CombatCharacterPanel>;

}

#endif // COMBATCHARACTERPANEL_HPP
