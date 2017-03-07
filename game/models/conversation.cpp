#include "conversation.hpp"
#include "utils/file.hpp"
#include "utils/typedefs.hpp"
#include "utils/exception.hpp"

#include <boost/algorithm/string.hpp>

#include <iostream>

namespace game {
namespace model {

ConversationStep::ConversationStep(const json& data)
{
  text = data["text"];
  sprite_path = data["head_sprite"];

  for(const auto& answer : data["answers"])
  {
    answers.push_back(answer["text"]);
    answers_action.emplace_back(answer["action"]["type"], answer["action"]["value"]);
  }
}

Conversation::Conversation(const json& data)
{
  const auto& conversation_data = data["conversation"];
  for(const auto& text : conversation_data["texts"])
  {
    ConversationStepSP step = std::make_shared<ConversationStep>(text);
    _steps.push_back(step);
  }

  _current = _steps.front();
}

void Conversation::playerChoose(size_t index)
{
  if(index >= _current->answers.size())
     assert("Conversion playerChoose index greater than number of answers");

  _current = _steps.at(index);
}

AnswerAction Conversation::answerAction(size_t offset) const noexcept
{
  if(offset >= _current->answers_action.size())
    return {};

   return _current->answers_action.at(offset);
}

const std::string& Conversation::answer(size_t offset) const noexcept
{
  if(offset >= _current->answers.size())
    return EMPTYSTR;

   return _current->answers.at(offset);
}

}
}
