#ifndef CHANGEMAP_HPP
#define CHANGEMAP_HPP

#include "game/interaction.hpp"

namespace game {

class ChangeMap final : public Interaction
{
  public:

    ChangeMap(const json& data);

    virtual void mouseHover() override;
    virtual void exec() override;
    virtual json save() override;
};

}

#endif // CHANGEMAP_HPP
