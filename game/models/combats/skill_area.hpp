#ifndef SKILLAREA_HPP
#define SKILLAREA_HPP

#include <memory>

#include "game/models/map_pos.hpp"
#include "utils/json.hpp"

namespace game {

class SkillArea;
using SkillAreaSP = std::shared_ptr<SkillArea>;

class SkillArea
{
  public:

    static SkillAreaSP create(const json& data);

    SkillArea(const json& data);
    virtual ~SkillArea() = default;

    virtual std::vector<MapPos> affectedMapPos(const MapPos& origin) const noexcept = 0;
    short getWidth() { return _width; }
    short getHeight() { return _height; }
    short getRange() { return _range; }

  protected:

    short _width {0};
    short _height {0};
    short _range {0};
};

}

#endif // SKILLAREA_HPP
