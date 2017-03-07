#ifndef COMBATTIMELINE_HPP
#define COMBATTIMELINE_HPP

#include "graphics/drawable.hpp"
#include "game/models/character.hpp"
#include "game/models/combat_model.hpp"

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
{
  public:

    CombatTimeLine(const sf::Vector2f& pos, const game::CombatModelSP& model);

    virtual void setPosition(float x, float y) override;

    virtual sf::FloatRect getGlobalBounds() const override;
    virtual void update(const sf::Time& time) override;

    virtual void setColor(const sf::Color& /*color*/) override {}
    virtual const sf::Color getColor() const override { return {}; }

  protected:

    virtual void internalDraw(sf::RenderTarget& target, sf::RenderStates states) const noexcept;
    void setCharacters();
    void setPointerPos(size_t index);

  private:

    SpriteSP _background;
    std::vector<SpriteSP> _pointers;
    std::list<CombatTimeLineFace> _faces;
    sf::Vector2f _pos;
    game::CombatModelSP _model;
};

using CombatTimeLineSP = std::shared_ptr<CombatTimeLine>;

}

#endif // COMBATTIMELINE_HPP
