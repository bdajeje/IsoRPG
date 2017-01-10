#ifndef INTERACTION_HPP
#define INTERACTION_HPP

#include <queue>

#include "graphics/sprite.hpp"
#include "utils/serializable.hpp"

namespace game {

enum class InteractionType {
  StartConversation,
  OpenTreasure,
  ChangeMap,
  Undefined
};

class Interaction;
using InteractionSP = std::shared_ptr<Interaction>;

class Interaction : public utils::Serializable
{
  public:

    static void send(const InteractionSP& interaction);
    static InteractionSP pop();
    static InteractionSP create(const json& data, graphics::SpriteSP& sprite);

    Interaction(const json& data, InteractionType type);
    virtual ~Interaction() = default;

    InteractionType type() const noexcept { return _type; }

    virtual void mouseHover();
    virtual void mouseLeave();
    virtual void exec() {}

  protected:

    InteractionType _type;
    json _data;

    static std::queue<InteractionSP> s_pending_interactions;
};

}

#endif // INTERACTION_HPP
