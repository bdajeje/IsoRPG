#include "conversation_screen.hpp"
#include "managers/texture_manager.hpp"
#include "managers/font_manager.hpp"
#include "utils/graphics.hpp"
#include "utils/mathematics.hpp"
#include "utils/file.hpp"
#include "managers/window.hpp"
#include "graphics/animations/text_color_transition.hpp"
#include "graphics/animations/bouncing_sprite.hpp"
#include "graphics/models/rectangle.hpp"

#include <iostream>

namespace game {
namespace screen {

namespace colors {
  const sf::Color AnswerSelected   = sf::Color(0, 0, 100);
  const sf::Color AnswerUnSelected = sf::Color::White;
}

namespace {
  constexpr float X_BG_OFFSET = 70;
}

ConversationScreen::ConversationScreen(const std::string& conversation_filepath)
  : _conversation (json::parse(utils::files::read("./resources/conversations/" + conversation_filepath)))
{
  const sf::Vector2u window_size = mgr::Window::instance()->getSize();

  SpriteSP background = graphics::getSprite("conversation_background.png", 1000, 300);
  utils::graphics::centerHonrizontally(background, window_size);
  background->move(0, 3 * (window_size.y / 5));

  const sf::FloatRect bg_bounds = background->getGlobalBounds();
  const sf::Vector2f& bg_pos = background->getPosition();
  const float answers_height {bg_bounds.height * 0.4f};

  // PNJ background
  RectangleSP pnj_head_background = std::make_shared<graphics::Rectangle>(110, 120, sf::Color(0, 0, 0, 180));
  pnj_head_background->setPosition(bg_pos.x + 10, bg_pos.y + 110);
  addDrawable(pnj_head_background);

  // Conversation PNG head sprite
  _conversation_head = graphics::getSprite("conversations/hidden.png", 95, 95);
  _conversation_head->setPosition(bg_pos.x + 20, bg_pos.y + 130);
  addDrawable(_conversation_head);

  sf::FloatRect conversation_bounds = utils::maths::boundsSteching(background->getGlobalBounds(), -150);
  conversation_bounds.height /= 2;
  _conversation_text.reset(new graphics::MultiLineContainer {"conversation.ttf", 16, sf::Color(200, 200, 200), conversation_bounds});

  addDrawable(background);
  addDrawable(_conversation_text);
  size_t i = 0;
  for(Answer& answer : _answers)
  {
	answer.text = graphics::getText("conversation.ttf", "", 15, colors::AnswerUnSelected);
	addDrawable(answer.text);
	addHoverable(answer.text, [=]() { focusAnswer(i); }, [=]() { unFocusAnswer(_focused_answer); });
	i++;
  }

  _conversation_text->setPosition(bg_pos.x + 140, bg_pos.y + 65);

  // Vertical Align answers at bottom of background
  std::vector<graphics::TextSP> answer_texts;
  answer_texts.reserve(_answers.size());
  for(Answer& answer : _answers)
	answer_texts.push_back(answer.text);
  utils::graphics::vAlign(answer_texts, _conversation_text->getPosition().x, bg_pos.y + bg_bounds.height - answers_height, answers_height);

  // Bounce sprite and animation
  _bounce_sprite = graphics::getSprite("conversation_next_step.png", 20, 20);
  _bounce_sprite->setPosition(bg_pos.x + (bg_bounds.width - _bounce_sprite->getGlobalBounds().width) / 2 + X_BG_OFFSET,
							  bg_pos.y + bg_bounds.height - _bounce_sprite->getGlobalBounds().height - 25);
  addDrawable(_bounce_sprite);
  addAnimation(std::make_shared<graphics::animations::BouncingSprite>(_bounce_sprite, 0, window_size.y * 0.01, sf::milliseconds(800)));

  // PNJ name
  _pnj_name = graphics::getText("conversation.ttf", "Mr Relou", 18, colors::AnswerUnSelected); // \todo: take name from json conversation
  _pnj_name->setPosition(bg_pos.x + X_BG_OFFSET + (bg_bounds.width - _pnj_name->getGlobalBounds().width) / 2, bg_pos.y + 15);
  addDrawable(_pnj_name);

  updateConversation();
}

void ConversationScreen::update(const sf::Time& elapsed_time)
{
  using namespace graphics::animations;

  InteractibleScreen::update(elapsed_time);
  _conversation_text->update(elapsed_time);

  // Start answers animation if not done and conversation text all shown
  if(!_answers_shown)
  {
	if(_conversation_text->isAllShown())
	{
	  _answers_shown = true;

	  // Start answers fade in
	  for(Answer& answer : _answers)
	  {
		auto animation = std::make_shared<FadingAnimation>(answer.text, sf::milliseconds(300), FadingAnimation::Type::In);
		animation->start();
		addAnimation(animation);
	  }

	  // Focus first answer
	  focusAnswer(0);
	}
	else if(_conversation_text->isCurrentShown() && _conversation_text->hasNext())
	  _bounce_sprite->show();
  }
}

void ConversationScreen::updateConversation()
{
  _answers_shown = false;
  _bounce_sprite->hide();
  _conversation_text->setString(_conversation.text());

  _conversation_head->setTexture(texture::TextureManager::get(_conversation.spritePath()));

  size_t i {0};
  for(Answer& answer : _answers)
  {
	answer.text->setString(_conversation.answer(i));
	answer.text->hide();
	i++;
  }
}

events::EventAction ConversationScreen::handleEvents(const sf::Event& event)
{
  const events::EventAction action = InteractibleScreen::handleEvents(event);
  if(action != events::EventAction::Continue)
    return action;

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wswitch"
  switch(event.type)
  {
    case sf::Event::MouseButtonReleased:
    {
      if(event.mouseButton.button == sf::Mouse::Button::Left)
      return clickAnswer(event.mouseButton.x, event.mouseButton.y);
      break;
    }
    case sf::Event::KeyPressed:
    {
      if(isKeyAllowed(utils::KeyBinding::key(KeyAction::ConversationFocusPreviousAnswer)))
        focusAnswer(_focused_answer - 1);
      else if(isKeyAllowed(utils::KeyBinding::key(KeyAction::ConversationFocusNextAnswer)))
        focusAnswer(_focused_answer + 1);
      else if(isKeyAllowed(utils::KeyBinding::key(KeyAction::ConversationSkip)))
      {
        if(!_answers_shown)
        {
          if(!_conversation_text->isCurrentShown())
            _conversation_text->finishAnimation();
          else
          {
            _conversation_text->next();
            _bounce_sprite->hide();
          }
        }
      }
      else if(isKeyAllowed(utils::KeyBinding::key(KeyAction::ConversationSelect)))
        return selectAnswer(_focused_answer);
      else if(isKeyAllowed(utils::KeyBinding::key(KeyAction::ConversationSelect1)))
        return selectAnswer(0);
      else if(isKeyAllowed(utils::KeyBinding::key(KeyAction::ConversationSelect2)))
        return selectAnswer(1);
      else if(isKeyAllowed(utils::KeyBinding::key(KeyAction::ConversationSelect3)))
        return selectAnswer(2);
      else if(isKeyAllowed(utils::KeyBinding::key(KeyAction::ConversationSelect4)))
        return selectAnswer(3);
      else if(isKeyAllowed(utils::KeyBinding::key(KeyAction::ConversationSelect5)))
        return selectAnswer(4);
    }
  }
#pragma GCC diagnostic pop

  return events::EventAction::Stop;
}

events::EventAction ConversationScreen::clickAnswer(int x, int y)
{
  if(!_answers_shown)
    return events::EventAction::Stop;

  size_t i = 0;
  for(auto answer : _answers)
  {
    if(answer.text->getGlobalBounds().contains(x, y))
      return selectAnswer(i);

    i++;
  }

  return events::EventAction::Stop;
}

events::EventAction ConversationScreen::selectAnswer(size_t offset) noexcept
{
  using namespace game::model;

  if(!_answers_shown)
    return events::EventAction::Stop;

  if(offset >= _conversation.nbrAnswers())
  {
    std::cerr << "Asking for answer" << offset << "would lead to buffer overfow, abort." << std::endl;
    return events::EventAction::Exit;
  }

  AnswerAction action = _conversation.answerAction(offset);
  switch(action.type)
  {
    case AnswerActionType::QuitConversation:
      return events::EventAction::ExitScreen;
    case AnswerActionType::RunScript:
      // \todo
      return events::EventAction::ExitScreen;
    case AnswerActionType::GotoConversationStep:
      _conversation.playerChoose(std::stoi(action.data));
      updateConversation();
      break;
  }

  return events::EventAction::Stop;
}

void ConversationScreen::focusAnswer(int offset)
{
  unFocusAnswer(_focused_answer);

  if(offset < 0)
    _focused_answer = nbrAnswers() - 1;
  else if(offset >= nbrAnswers())
    _focused_answer = 0;
  else
    _focused_answer = offset;

  addAnimation(std::make_shared<graphics::animations::TextColorTransition>(_answers[_focused_answer].text, colors::AnswerSelected, sf::milliseconds(300)));
}

void ConversationScreen::unFocusAnswer(int offset)
{
  if(offset < 0 || offset >= _answers.size() - 1)
    return;

  addAnimation(std::make_shared<graphics::animations::TextColorTransition>(_answers[offset].text, colors::AnswerUnSelected, sf::milliseconds(300)));
}

}
}
