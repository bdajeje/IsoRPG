#include "start_conversation_interaction.hpp"
#include "game/game.hpp"
#include "game/screens/conversation_screen.hpp"
#include "graphics/mouse.hpp"

namespace game {

StartConversationInteraction::StartConversationInteraction(const json& data)
  : Interaction (data, InteractionType::StartConversation)
{}

void StartConversationInteraction::exec()
{
  const std::string& conversation_name = _data[0]["name"];
  Game::show(std::make_shared<screen::ConversationScreen>(conversation_name));
}

json StartConversationInteraction::save()
{
  return _data;
}

void StartConversationInteraction::mouseHover()
{
  graphics::Mouse::setStatus(graphics::Mouse::Status::StartConversation);
}

}
