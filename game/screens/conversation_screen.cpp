#include "conversation_screen.hpp"
#include "managers/texture_manager.hpp"
#include "managers/font_manager.hpp"
#include "utils/graphics.hpp"
#include "utils/mathematics.hpp"
#include "managers/window.hpp"
#include "graphics/animations/text_color_transition.hpp"
#include "graphics/animations/bouncing_sprite.hpp"

#include <iostream>

namespace game {
namespace screen {

namespace colors {
  const sf::Color AnswerSelected   = sf::Color::Blue;
  const sf::Color AnswerUnSelected = sf::Color::White;
}

namespace {

  constexpr float HeadSpriteWidthRatio {0.1};
  constexpr float HeadSpriteHeightRatio {0.1};

}

ConversationScreen::ConversationScreen(const std::string& conversation_filepath)
  : _conversation (conversation_filepath)
  , _limitor {200}
{
  const sf::Vector2u window_size = mgr::Window::instance()->getSize();

  SpriteSP background = graphics::getSprite("conversation_background.png", 0.6, 0.35);

  const int bg_padding {20};
  const sf::FloatRect bg_bounds = background->getGlobalBounds();
  const float answers_height {bg_bounds.height * 0.4f};

  sf::FloatRect conversation_bounds = utils::maths::boundsSteching(background->getGlobalBounds(), -bg_padding);
  conversation_bounds.height /= 2;
  _conversation_text.reset(new graphics::MultiLineContainer {"conversation.ttf", 16, sf::Color(59, 159, 131), conversation_bounds});

  addDrawable(background);
  addDrawable(_conversation_text);
  for(Answer& answer : _answers)
  {
    answer.text = graphics::getText("conversation.ttf", "", 15, colors::AnswerUnSelected);
    addDrawable(answer.text);
  }

  utils::graphics::centerHonrizontally(background, window_size);
  background->move(0, 3 * (window_size.y / 5));

  const sf::Vector2f& bg_pos = background->getPosition();
  _conversation_text->setPosition(bg_pos.x + bg_padding, bg_pos.y + bg_padding);

  // Vertical Align answers at bottom of background
  std::vector<graphics::TextSP> answer_texts;
  answer_texts.reserve(_answers.size());
  for(Answer& answer : _answers)
    answer_texts.push_back(answer.text);
  utils::graphics::vAlign(answer_texts, bg_pos.x + bg_padding, bg_pos.y + bg_bounds.height - answers_height, answers_height);

  // Bounce sprite and animation
  _bounce_sprite = graphics::getSprite("conversation_next_step.png", 0.02, 0.02);
  _bounce_sprite->setPosition(bg_pos.x + (bg_bounds.width - _bounce_sprite->getGlobalBounds().width) / 2,
                              bg_pos.y + (bg_bounds.height * 0.7));
  addDrawable(_bounce_sprite);
  addAnimation(std::make_shared<graphics::animations::BouncingSprite>(_bounce_sprite, 0, window_size.y * 0.01, sf::milliseconds(800)));

  // Conversation PNG head sprite background
  SpriteSP conversation_head_bg = graphics::getSprite("conversation_background.png", HeadSpriteWidthRatio, HeadSpriteHeightRatio);
  conversation_head_bg->setPosition(bg_pos.x, bg_pos.y - conversation_head_bg->getGlobalBounds().height - 5);
  addDrawable(conversation_head_bg);

  // Conversation PNG head sprite
  _conversation_head = graphics::getSprite("conversations/hidden.png", HeadSpriteWidthRatio, HeadSpriteHeightRatio);
  _conversation_head->setPosition(conversation_head_bg->getPosition());
  addDrawable(_conversation_head);

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
        auto animation = std::make_shared<FadingAnimation>(answer.text, sf::milliseconds(300));
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
//  graphics::resizeSprite(_conversation_head, HeadSpriteWidthRatio, HeadSpriteHeightRatio);

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
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wswitch"
  switch(event.type)
  {
    case sf::Event::KeyPressed:
    {
      if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && _limitor.isAllow(sf::Keyboard::Up))
        focusAnswer(_focused_answer - 1);
      else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && _limitor.isAllow(sf::Keyboard::Down))
        focusAnswer(_focused_answer + 1);
      else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && _limitor.isAllow(sf::Keyboard::Space))
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
      else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && _limitor.isAllow(sf::Keyboard::Return))
      {
        if(_answers_shown)
          return selectAnswer(_focused_answer);
      }
    }
  }
#pragma GCC diagnostic pop

  return events::EventAction::Stop;
}

events::EventAction ConversationScreen::selectAnswer(size_t offset) noexcept
{
  using namespace game::model;

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
      return events::EventAction::Continue;
    case AnswerActionType::GotoConversationStep:
      _conversation.playerChoose(std::stoi(action.data));
      updateConversation();
      return events::EventAction::Continue;
  }

  return events::EventAction::Continue;
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
