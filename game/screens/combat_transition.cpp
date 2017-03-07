#include "combat_transition.hpp"
#include "managers/window.hpp"
#include "graphics/animations/fading_animation.hpp"
#include "graphics/animations/move.hpp"
#include "graphics/models/rectangle.hpp"
#include "utils/random.hpp"

namespace game {
namespace screen {

static std::array<CombatTransition::Transition, 3> Transitions {
  CombatTransition::Transition::CornersExit,
  CombatTransition::Transition::HorizontalSplit,
  CombatTransition::Transition::VerticalSplit
};

CombatTransition::CombatTransition()
  : _animation_time {sf::milliseconds(1000)}
{
  _texture.create(mgr::Window::width(), mgr::Window::height());
  _texture.update(*mgr::Window::instance().get());

  auto index = utils::random(0, Transitions.size());
  create(Transitions.at(index));
}

void CombatTransition::update(const sf::Time& elapsed_time)
{
  InteractibleScreen::update(elapsed_time);

  if(!_animation || _animation->isFinished())
    _finish = true;
}

events::EventAction CombatTransition::handleEvents(const sf::Event& /*event*/)
{
  return events::EventAction::Stop;
}

void CombatTransition::create(Transition transition)
{
  const int window_width = mgr::Window::instance()->getSize().x;
  const int window_height = mgr::Window::instance()->getSize().y;

  // Always create a black background than fades away behind the effects
  auto background = std::make_shared<graphics::Rectangle>(window_width, window_height, sf::Color(50,0,0));
  auto bg_animation = std::make_shared<graphics::animations::FadingAnimation>(background, _animation_time, graphics::animations::FadingAnimation::Type::Out);
  background->addAnimation(bg_animation);
  _animation = bg_animation;
  addDrawable(background);

  switch(transition)
  {
    case Transition::CornersExit:
    {
      std::vector<graphics::SpriteSP> sprites = prepareSprites(4);
      const auto width = window_width / 2;
      const auto height = window_height / 2;

      // Top Left
      sprites[0]->setPosition(0, 0);
      sprites[0]->setTextureRect( sf::IntRect{0, 0, width, height} );
      sprites[0]->addAnimation( std::make_shared<graphics::animations::Move>(sprites[0], -width, -height, _animation_time) );

      // Top Right
      sprites[1]->setPosition(width, 0);
      sprites[1]->setTextureRect( sf::IntRect{width, 0, width, height} );
      sprites[1]->addAnimation( std::make_shared<graphics::animations::Move>(sprites[1], width, -height, _animation_time) );

      // Bottom Left
      sprites[2]->setPosition(0, height);
      sprites[2]->setTextureRect( sf::IntRect{0, height, width, height} );
      sprites[2]->addAnimation( std::make_shared<graphics::animations::Move>(sprites[2], -width, height, _animation_time) );

      // Bottom Right
      sprites[3]->setPosition(width, height);
      sprites[3]->setTextureRect( sf::IntRect{width, height, width, height} );
      sprites[3]->addAnimation( std::make_shared<graphics::animations::Move>(sprites[3], width, height, _animation_time) );

      break;
    }
    case Transition::HorizontalSplit:
    {
      std::vector<graphics::SpriteSP> sprites = prepareSprites(2);
      const auto height = window_height / 2;
      const int multiplicator = utils::random(0, 2) == 0 ? 1 : -1;

      // Top
      sprites[0]->setPosition(0, 0);
      sprites[0]->setTextureRect( sf::IntRect{0, 0, window_width, height} );
      sprites[0]->addAnimation( std::make_shared<graphics::animations::Move>(sprites[0], -multiplicator * window_width, 0, _animation_time) );

      // Top Bottom
      sprites[1]->setPosition(0, height);
      sprites[1]->setTextureRect( sf::IntRect{0, height, window_width, height} );
      sprites[1]->addAnimation( std::make_shared<graphics::animations::Move>(sprites[1], multiplicator * window_width, 0, _animation_time) );

      break;
    }
    case Transition::VerticalSplit:
    {
      std::vector<graphics::SpriteSP> sprites = prepareSprites(2);
      const auto width = window_width / 2;
      const int multiplicator = utils::random(0, 2) == 0 ? 1 : -1;

      // Top
      sprites[0]->setPosition(0, 0);
      sprites[0]->setTextureRect( sf::IntRect{0, 0, width, window_height} );
      sprites[0]->addAnimation( std::make_shared<graphics::animations::Move>(sprites[0], 0, -multiplicator * window_height, _animation_time) );

      // Top Bottom
      sprites[1]->setPosition(width, 0);
      sprites[1]->setTextureRect( sf::IntRect{width, 0, width, window_height} );
      sprites[1]->addAnimation( std::make_shared<graphics::animations::Move>(sprites[1], 0, multiplicator * window_height, _animation_time) );

      break;
    }
  }
}

std::vector<graphics::SpriteSP> CombatTransition::prepareSprites(size_t nbr_parts)
{
  const int window_width = mgr::Window::instance()->getSize().x;
  const int window_height = mgr::Window::instance()->getSize().y;

  std::vector<graphics::SpriteSP> sprites;
  sprites.reserve(nbr_parts);
  for(size_t i = 0; i < nbr_parts; ++i)
  {
    auto sprite = graphics::getSprite(_texture, window_width, window_height);
    sprites.push_back(sprite);
    sprite->addAnimation(std::make_shared<graphics::animations::FadingAnimation>(sprite, _animation_time, graphics::animations::FadingAnimation::Type::Out));
    addDrawable(sprite);
  }

  return sprites;
}

}
}
