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

    /* Use static inist method to instanciate the singleton (for the game)
     * Use the constructor to get a temporary objects (usefull to get info on a saved game)
     */
    static void init(const std::string& save_name);
    CharactersTeam(const std::string& save_name);

    static std::shared_ptr<CharactersTeam> instance() { return _instance; }
    uint money() { return _money; }
    size_t nbrCharacters() { return _characters.size(); }
    PlayableCharacterSP character(size_t offset) noexcept;
    PlayableCharacterSP& currentCharacter() { return _current_map_character; }
    std::vector<PlayableCharacterSP>& characters() { return _characters; }

    json save() override;

  private:

    std::vector<PlayableCharacterSP> _characters;
    uint _money;
    PlayableCharacterSP _current_map_character;
    static std::shared_ptr<CharactersTeam> _instance;
};

}

#endif // CHARACTERSTEAM_HPP
