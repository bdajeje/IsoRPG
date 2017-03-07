#ifndef GAME_MODEL_CONVERSATION_HPP
#define GAME_MODEL_CONVERSATION_HPP

#include <string>
#include <memory>
#include <vector>

#include "utils/json.hpp"

namespace game {
namespace model {

enum class AnswerActionType
{
  QuitConversation,
  RunScript,
  GotoConversationStep
};

struct AnswerAction
{
    AnswerAction(const std::string& type_str, const std::string& data)
      : data {data}
    {
      if(type_str == "goto")
        type = AnswerActionType::GotoConversationStep;
      else if(type_str == "script")
        type = AnswerActionType::RunScript;
      else if(type_str == "quit")
        type = AnswerActionType::QuitConversation;
      else
        type = AnswerActionType::QuitConversation;
    }

    AnswerAction()
      : AnswerAction{"quit", ""}
    {}

    AnswerActionType type {AnswerActionType::QuitConversation};
    std::string data;
};

struct ConversationStep
{
  ConversationStep(const json& data);

  std::string text;
  std::string sprite_path;
  std::vector<std::string> answers;
  std::vector<AnswerAction> answers_action;
};

using ConversationStepSP = std::shared_ptr<ConversationStep>;

class Conversation final
{
  public:

    Conversation(const json& data);

    const std::string& text() const noexcept { return _current->text; }
    const std::string& spritePath() const noexcept { return _current->sprite_path; }
    const std::string& answer(size_t offset) const noexcept;
    AnswerAction answerAction(size_t offset) const noexcept;
    size_t nbrAnswers() const noexcept { return _current->answers.size(); }    

    void playerChoose(size_t index);

  private:

    std::vector<ConversationStepSP> _steps;
    std::shared_ptr<ConversationStep> _current;
};

}
}

#endif // GAME_MODEL_CONVERSATION_HPP
