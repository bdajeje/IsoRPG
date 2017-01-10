#include "conversation.hpp"
#include "utils/file.hpp"
#include "utils/typedefs.hpp"
#include "utils/exception.hpp"

#include <boost/algorithm/string.hpp>

#include <iostream>

namespace game {
namespace model {

namespace {

  AnswerAction createAnswerAction(const std::string& input) noexcept
  {
    AnswerAction action;

    if(input.size() < 3)
      return action;

    action.data = input.substr(2);

    // Continue conversation to selected step
    if(input.front() == 'c')
      action.type = AnswerActionType::GotoConversationStep;
    // Run script
    else if(input.front() == 's')
      action.type = AnswerActionType::RunScript;
    // Defined action
    else if(input.front() == 'a')
    {
      action.type = AnswerActionType::QuitConversation;
    }

    return action;
  }

}

namespace {
  typedef const std::vector<std::string> Lines;
  typedef std::vector<std::string>::const_iterator Lines_cit;

  void setConversationStepText(ConversationStepSP& step, Lines_cit& it)
  {
    const std::string line = *it;
    std::vector<std::string> parts;
    parts.reserve(2);
    boost::algorithm::split(parts, line, boost::is_any_of("|"));
    if(parts.size() != 2)
      throw utils::Exception("Wrong conversation step line: " + line);

    step->text = parts[0];
    step->sprite_path = parts[1];
    ++it;
  }

  void setConversationStepAnswers(ConversationStepSP& step, Lines_cit& it)
  {
    uint nbr_answers = std::stoul(*it);
    do {
      ++it;
      nbr_answers--;
      const std::string line = *it;
      std::vector<std::string> parts;
      parts.reserve(2);
      boost::algorithm::split(parts, line, boost::is_any_of("|"));
      if(parts.size() != 2)
        throw utils::Exception("Wrong conversation answer: " + line);
      step->answers.emplace_back(parts[0]);
      step->answers_action.emplace_back(createAnswerAction(parts[1]));
    }
    while(nbr_answers > 0);
  }
}

Conversation::Conversation(const std::string& conversation_filepath)
{
  Lines lines = utils::files::lines("./resources/conversations/" + conversation_filepath);
  Lines_cit it = lines.begin();
  Lines_cit end = lines.end();
  while(it != end && !(*it).empty())
  {
    ConversationStepSP step = std::make_shared<ConversationStep>();
    setConversationStepText(step, it);
    setConversationStepAnswers(step, it);    
    _steps.push_back(step);
    ++it;
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

   return _current->answers.at(offset).text;
}

}
}
