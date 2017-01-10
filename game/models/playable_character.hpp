#ifndef PLAYABLECHARACTER_HPP
#define PLAYABLECHARACTER_HPP

#include "game/models/character.hpp"

namespace game {

class PlayableCharacter final : public Character
{
  public:

    PlayableCharacter(const json& data);

    uint exp() const noexcept { return _exp._value; }
    uint maxExp() const noexcept { return _exp._max; }
    float expRatio() const noexcept { return _exp._max != 0.f ? static_cast<float>(_exp._value) / static_cast<float>(_exp._max) : 0.f; }
    size_t startMovementRange() const noexcept { return _start_movement_range; }

    const std::string& standingTextureName() const noexcept { return _standing_texture_name; }

    virtual json save() override;

  private:

    std::string _standing_texture_name;
    MaxedValue<uint> _exp;
    size_t _start_movement_range;
};

using PlayableCharacterSP = std::shared_ptr<PlayableCharacter>;

}

#endif // PLAYABLECHARACTER_HPP
