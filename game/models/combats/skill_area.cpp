#include "skill_area.hpp"

#include "cross_skill_area.hpp"

namespace game {

SkillAreaSP SkillArea::create(const json& data)
{
  const std::string type = data["type"];

  if(type == "cross")
    return std::make_shared<CrossSkillArea>(data);

  return nullptr;
}

SkillArea::SkillArea(const json& data)
{
  _width = data["width"];
  _height = data["height"];
  _range = data["range"];
}

}
