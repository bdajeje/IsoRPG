#ifndef CHARACTERSTEAM_HPP
#define CHARACTERSTEAM_HPP

#include <vector>
#include <memory>

#include "game/models/playable_character.hpp"
#include "game/models/map_pos.hpp"
#include "utils/serializable.hpp"

namespace game {

class CharactersTeam final : public utils::Serializable
{
  public:

    static constexpr size_t MaxNbrCharacters {4};

    static void init();
    static std::shared_ptr<CharactersTeam> instance() { return _instance; }
    static uint money() { return _instance->_money; }
    static size_t nbrCharacters() { return _instance->_characters.size(); }    
    static PlayableCharacterSP character(size_t offset) noexcept;
    static PlayableCharacterSP& currentCharacter() { return _instance->_current_map_character; }
    static std::vector<PlayableCharacterSP>& characters() { return _instance->_characters; }

    json save() override;

  private:

    CharactersTeam();

  private:

    std::vector<PlayableCharacterSP> _characters;
    uint _money;
    PlayableCharacterSP _current_map_character;
    static std::shared_ptr<CharactersTeam> _instance;
};

}

#endif // CHARACTERSTEAM_HPP
