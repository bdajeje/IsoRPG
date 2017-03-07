#ifndef CHARACTERSKILL_HPP
#define CHARACTERSKILL_HPP

#include <string>

#include "utils/json.hpp"

namespace game {

class CharacterSkill
{
  public:

    CharacterSkill(const json& data);
    virtual ~CharacterSkill() = default;

    const std::string& icon() const noexcept { return _icon; }

  private:

    std::string _icon;
};

}

#endif // CHARACTERSKILL_HPP
