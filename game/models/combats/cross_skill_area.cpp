#include "cross_skill_area.hpp"

namespace game {

CrossSkillArea::CrossSkillArea(const json& data)
  : SkillArea {data}
{}

std::vector<MapPos> CrossSkillArea::affectedMapPos(const MapPos& origin) const noexcept
{
  std::vector<MapPos> results;
  results.reserve(_width + _height + 1);

  results.emplace_back(origin);

  for(auto i = -_width / 2; i <= (_width / 2); ++i)
    results.emplace_back(origin.x + i, origin.y);

  for(auto i = -_height / 2; i <= (_height / 2); ++i)
    results.emplace_back(origin.x, origin.y + i);

  return results;
}

}
