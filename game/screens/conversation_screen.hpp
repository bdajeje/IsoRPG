#ifndef CONVERSATION_SCREEN_HPP
#define CONVERSATION_SCREEN_HPP

#include "game/interactible_screen.hpp"
#include "game/models/conversation.hpp"
#include "managers/font_manager.hpp"
#include "graphics/models/container.hpp"
#include "graphics/multi_line_container.hpp"
#include "graphics/text.hpp"
#include "graphics/animations/fading_animation.hpp"
#include "utils/key_limitor.hpp"

namespace game {
namespace screen {

struct Answer
{
  graphics::TextSP text;
  graphics::animations::FadingAnimationSP animation;
};

class ConversationScreen final : public InteractibleScreen
{
  public:

    ConversationScreen(const std::string& conversation_filepath);

    events::EventAction handleEvents(const sf::Event& event) override;

    virtual void update(const sf::Time& elapsed_time) override;

  private:

    void updateConversation();
    void focusAnswer(int offset);
    void unFocusAnswer(int offset);
    size_t nbrAnswers() const { return _conversation.nbrAnswers(); }
    events::EventAction selectAnswer(size_t offset) noexcept;

  private:

    graphics::MultiLineContainerSP _conversation_text;
    std::array<Answer, 5> _answers;
    model::Conversation _conversation;
    bool _answers_shown {false};
    size_t _focused_answer {0};
    utils::KeyLimitor _limitor;
    graphics::SpriteSP _bounce_sprite;
    graphics::SpriteSP _conversation_head;
//    model::ConversationProgress _conversation_progress;
};

}
}

#endif // CONVERSATION_SCREEN_HPP
