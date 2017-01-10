#ifndef GAME_MODEL_CONVERSATION_HPP
#define GAME_MODEL_CONVERSATION_HPP

#include <string>
#include <memory>
#include <vector>

namespace game {
namespace model {

enum class AnswerActionType
{
  QuitConversation,
  RunScript,
  GotoConversationStep
};

struct ConversationAnswer
{
    ConversationAnswer(std::string text)
      : text {text}
    {}

    std::string text;
};

struct AnswerAction
{
    AnswerActionType type {AnswerActionType::QuitConversation};
    std::string data;
};

struct ConversationStep
{
  std::string text;
  std::string sprite_path;
  std::vector<ConversationAnswer> answers;
  std::vector<AnswerAction> answers_action;
};

using ConversationStepSP = std::shared_ptr<ConversationStep>;

class Conversation final
{
  public:

    Conversation(const std::string& conversation_filepath);

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
