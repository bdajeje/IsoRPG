#ifndef COMBATTIMELINE_HPP
#define COMBATTIMELINE_HPP

#include "graphics/drawable.hpp"
#include "game/transformable.hpp"
#include "game/models/character.hpp"

namespace graphics {

struct CombatTimeLineFace
{
    CombatTimeLineFace(SpriteSP sprite, game::CharacterSP character)
      : _sprite {sprite}
      , _character {character}
    {}

    SpriteSP _sprite;
    game::CharacterSP _character;
};

class CombatTimeLine final : public Drawable
                           , public game::Transformable
{
  public:

    CombatTimeLine(const sf::Vector2f& pos, const std::list<game::CharacterSP>& characters);

    void setPosition(float x, float y) override;
    void setPosition(const sf::Vector2f& position) override { setPosition(position.x, position.y); }    

    virtual sf::FloatRect getGlobalBounds() const override;
    virtual void update(const sf::Time& time) override;

    virtual void setColor(const sf::Color& /*color*/) override {}
    virtual const sf::Color getColor() const override { return {}; }

  protected:

    virtual void internalDraw(sf::RenderTarget& target, sf::RenderStates states) const noexcept;
    void setCharacters(const std::list<game::CharacterSP>& characters);

  private:

    std::list<game::CharacterSP> _characters;
    std::list<CombatTimeLineFace> _faces;
    sf::Vector2f _pos;
};

using CombatTimeLineSP = std::shared_ptr<CombatTimeLine>;

}

#endif // COMBATTIMELINE_HPP
