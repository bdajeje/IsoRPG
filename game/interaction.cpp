#include "interaction.hpp"
#include "game/interactions/start_conversation_interaction.hpp"
#include "game/interactions/treasure_interaction.hpp"
#include "game/interactions/change_map.hpp"
#include "graphics/mouse.hpp"

namespace game {

namespace {
  InteractionType typeFromStr(const std::string& input)
  {
    if(input == "conversation")
      return InteractionType::StartConversation;
    else if(input == "treasure")
      return InteractionType::OpenTreasure;
    else if(input == "change_map")
      return InteractionType::ChangeMap;
    else
      return InteractionType::Undefined;
  }
}

std::queue<InteractionSP> Interaction::s_pending_interactions;

void Interaction::send(const InteractionSP& interaction)
{
  s_pending_interactions.push(interaction);
}

InteractionSP Interaction::create(const json& data, graphics::SpriteSP& sprite)
{
  switch(typeFromStr(data["type"]))
  {
    case InteractionType::StartConversation:
      return std::make_shared<StartConversationInteraction>(data);
    case InteractionType::OpenTreasure:
      return std::make_shared<TreasureInteraction>(data, sprite);
    case InteractionType::ChangeMap:
      return std::make_shared<ChangeMap>(data);
  }

  return {};
}

InteractionSP Interaction::pop()
{
  if(s_pending_interactions.empty())
    return nullptr;

  InteractionSP front = s_pending_interactions.front();
  s_pending_interactions.pop();
  return front;
}

Interaction::Interaction(const json& data, InteractionType type)
  : _type {type}
  , _data {data}
{}

void Interaction::mouseHover()
{
  graphics::Mouse::setStatus(graphics::Mouse::Status::Hover);
}

void Interaction::mouseLeave()
{
  graphics::Mouse::setStatus(graphics::Mouse::Status::Normal);
}

}
