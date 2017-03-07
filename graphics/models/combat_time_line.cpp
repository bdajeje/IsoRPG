#include "combat_time_line.hpp"
#include "graphics/animations/delay.hpp"
#include "graphics/animations/fading_animation.hpp"
#include "graphics/animations/move.hpp"

namespace graphics {

namespace {
  constexpr float FACE_WIDTH = 40;
  constexpr float FACE_HEIGHT = 40;
}

CombatTimeLine::CombatTimeLine(const sf::Vector2f& pos, const game::CombatModelSP& model)
  : _pos {pos}
  , _model {model}
{
  _background = getSprite("combats/timeline_background.png", 300, 100);
  _transformable = _background->transformable();

  setCharacters();

  model->registerEvent(game::CombatModel::Event::CharacterTurn, [&](){
    _pointers.clear();
    _pointers.push_back(getSprite("combats/timeline_pointer.png", 15, 15));
    setPointerPos(0);
  });
}

void CombatTimeLine::internalDraw(sf::RenderTarget& target, sf::RenderStates states) const noexcept
{
  _background->draw(target, states);

  for(const auto& face : _faces)
    face._sprite->draw(target, states);

  for(const auto& pointer : _pointers)
    pointer->draw(target, states);
}

void CombatTimeLine::update(const sf::Time& time)
{
  for(const auto& face : _faces)
    face._sprite->update(time);
}

void CombatTimeLine::setCharacters()
{
  // Create faces
  _faces.clear();
  for(const auto& character : _model->characters())
  {
    SpriteSP face = getSprite(character->faceTextureName(), FACE_WIDTH, FACE_HEIGHT);
    face->hide();
    _faces.emplace_back(face, character);
  }

  setPosition(_pos.x, _pos.y);

  // Create animation
  int delay = 150;
  const int animation_time = 1000;
  float face_y_offset = 100;
  for(auto& face : _faces)
  {
    SpriteSP& sprite = face._sprite;
    sprite->move(0, -face_y_offset);

    auto fade_in_animation = std::make_shared<animations::FadingAnimation>(sprite, sf::milliseconds(animation_time * 2), animations::FadingAnimation::Type::In);
    auto delay_animation_1 = std::make_shared<animations::Delay>(fade_in_animation, sf::milliseconds(delay));
    sprite->addAnimation(delay_animation_1);

    auto move_animation = std::make_shared<animations::Move>(sprite, 0, face_y_offset, sf::milliseconds(animation_time));
    auto delay_animation_2 = std::make_shared<animations::Delay>(move_animation, sf::milliseconds(delay));
    sprite->addAnimation(delay_animation_2);

    delay += delay;
  }
}

void CombatTimeLine::setPosition(float x, float y)
{
  _background->setPosition(x, y);

  x += 25;
  y += 10;

  for(auto& face : _faces)
  {
    float y_offset = face._character->isAlly() ? 0 : 20;

    SpriteSP& sprite = face._sprite;
    sprite->setPosition(x, y + y_offset);
    x += sprite->getGlobalBounds().width + 10;
  }

  for(size_t i = 0, end = _pointers.size(); i < end; ++i)
    setPointerPos(i);
}

void CombatTimeLine::setPointerPos(size_t index)
{
  if(index >= _faces.size() || index >= _pointers.size())
    return;

  auto face = (*std::next(_faces.begin(), index));
  const auto& face_pos = face._sprite->getPosition();
  const auto& face_bound = face._sprite->getGlobalBounds();

  auto& pointer = _pointers[index];
  pointer->setPosition(face_pos.x + (face_bound.width - pointer->getGlobalBounds().width) / 2, face_pos.y + face_bound.height + 5);
}

sf::FloatRect CombatTimeLine::getGlobalBounds() const
{
  if(_faces.empty())
    return {_pos.x, _pos.y, 0, 0};

  const auto& face_left = _faces.front()._sprite;
  if(_faces.size() == 1)
    return {_pos.x, _pos.y, face_left->getGlobalBounds().width, face_left->getGlobalBounds().height};

  const auto& face_right = _faces.back()._sprite;
  return {
    _pos.x, _pos.y,
    face_right->getPosition().x + face_right->getGlobalBounds().width - _pos.x, face_left->getGlobalBounds().height
  };
}

}
