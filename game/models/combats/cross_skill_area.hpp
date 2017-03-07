#ifndef CROSSSKILLAREA_HPP
#define CROSSSKILLAREA_HPP

#include "game/models/combats/skill_area.hpp"

namespace game {

class CrossSkillArea final : public SkillArea
{
  public:

    CrossSkillArea(const json& data);

    std::vector<MapPos> affectedMapPos(const MapPos& origin) const noexcept;
};

}

#endif // CROSSSKILLAREA_HPP
