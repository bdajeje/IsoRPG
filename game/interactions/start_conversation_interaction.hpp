#ifndef STARTCONVERSATIONINTERACTION_HPP
#define STARTCONVERSATIONINTERACTION_HPP

#include "game/interaction.hpp"

namespace game {

class StartConversationInteraction final : public Interaction
{
  public:

    StartConversationInteraction(const json& data);

    virtual void exec() override;
    virtual json save() override;
    virtual void mouseHover() override;
};

}

#endif // STARTCONVERSATIONINTERACTION_HPP
