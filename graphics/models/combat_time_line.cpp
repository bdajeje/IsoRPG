#include "combat_time_line.hpp"
#include "graphics/animations/delay.hpp"
#include "graphics/animations/fading_animation.hpp"
#include "graphics/animations/move.hpp"

namespace graphics {

namespace {
  constexpr float FACE_WIDTH = 40;
  constexpr float FACE_HEIGHT = 40;
}

CombatTimeLine::CombatTimeLine(const sf::Vector2f& pos, const std::list<game::CharacterSP>& characters)
  : _pos {pos}
{
  setCharacters(characters);
}

void CombatTimeLine::internalDraw(sf::RenderTarget& target, sf::RenderStates states) const noexcept
{
  for(const auto& face : _faces)
    face._sprite->draw(target, states);
}

void CombatTimeLine::update(const sf::Time& time)
{
  for(const auto& face : _faces)
    face._sprite->update(time);
}

void CombatTimeLine::setCharacters(const std::list<game::CharacterSP>& characters)
{
  // Order characters
  _characters = characters;
  _characters.sort([](const game::CharacterSP& character_1, const game::CharacterSP& character_2) {
    return character_1->speed() < character_2->speed();
  });

  // Create faces
  _faces.clear();
  for(const auto& character : _characters)
  {
    SpriteSP face = getSprite(character->faceTextureName(), FACE_WIDTH, FACE_HEIGHT);
    face->hide();
    _faces.emplace_back(face, character);
  }

  setPosition(_pos);

  // Create animation
  int delay = 150;
  const int animation_time = 1000;
  float face_y_offset = 100;
  for(auto& face : _faces)
  {
    SpriteSP& sprite = face._sprite;
    sprite->move(0, face_y_offset);

    auto fade_in_animation = std::make_shared<animations::FadingAnimation>(sprite, sf::milliseconds(animation_time * 2));
    auto delay_animation_1 = std::make_shared<animations::Delay>(fade_in_animation, sf::milliseconds(delay));
    sprite->addAnimation(delay_animation_1);

    auto move_animation = std::make_shared<animations::Move>(sprite, 0, -face_y_offset, sf::milliseconds(animation_time));
    auto delay_animation_2 = std::make_shared<animations::Delay>(move_animation, sf::milliseconds(delay));
    sprite->addAnimation(delay_animation_2);

    delay += delay;
  }
}

void CombatTimeLine::setPosition(float x, float y)
{
  for(auto& face : _faces)
  {
    float y_offset = face._character->isAlly() ? 0 : 20;

    SpriteSP& sprite = face._sprite;
    sprite->setPosition(x, y + y_offset);
    x += sprite->getGlobalBounds().width + 10;
  }
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
