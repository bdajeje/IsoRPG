//#include "hacking.hpp"
//#include "graphics/sprite.hpp"
//#include "utils/graphics.hpp"
//#include "utils/mathematics.hpp"
//#include "managers/texture_manager.hpp"
//#include "managers/sound_manager.hpp"

//#include <iostream>

//namespace game {
//namespace screen {

//namespace {
//  constexpr int ROTATION = 6;
//  constexpr size_t NBR_BTNS = 16;
//}

//Hacking::Hacking()
//  : _neutral_texture {texture::TextureManager::get("hacking/empty_btn.png")}
//  ,_error_texture {texture::TextureManager::get("hacking/wrong_btn.png")}
//  ,_success_texture {texture::TextureManager::get("hacking/right_btn.png")}
//  , _limitor {50}
//  , _angle {utils::maths::random(0, 360)}
//  , _target_proximity {30}
//{
//  _target_angle = _angle + utils::maths::random(30, 330);

//  graphics::SpriteSP background = graphics::getSprite("hacking/background.png", 1, 1);
//  addDrawable(background);
//  const sf::FloatRect background_bounds = background->getGlobalBounds();

//  _rotor = graphics::getSprite("hacking/rotor.png");
//  const sf::FloatRect rotor_bounds = _rotor->getGlobalBounds();
//  _rotor->setOrigin(rotor_bounds.width / 2, rotor_bounds.height / 2);
//  _rotor->setPosition(background_bounds.width / 2, background_bounds.height / 2);
//  _rotor->setRotation(_angle);
//  addDrawable(_rotor);

//  graphics::SpriteSP joystick = graphics::getSprite("hacking/joystick.png");
//  joystick->setPosition((background_bounds.width - joystick->getGlobalBounds().width) / 2, background_bounds.height);
//  addDrawable(joystick);

//  _intro_animation = std::make_shared<graphics::animations::Move>(joystick, 0, -background_bounds.height / 2, sf::milliseconds(1000));
//  addAnimation(_intro_animation);

//  constexpr float btn_width {0.14};
//  constexpr float btn_height {0.01};
//  const float btns_total_height {background_bounds.height / 2.5};
//  const float btns_y {background_bounds.height / 3.25};
//  _right_btns.resize(NBR_BTNS);
//  _wrong_btns.resize(NBR_BTNS);

//  for(graphics::SpriteSP& sprite : _right_btns)
//  {
//    sprite = graphics::getSprite(_neutral_texture, btn_width, btn_height);
//    addDrawable(sprite);
//  }
//  utils::graphics::vAlign(_right_btns, background_bounds.width / 6, btns_y, btns_total_height);
//  utils::graphics::hCircleAlign(_right_btns, 0.1 * background_bounds.width);

//  for(graphics::SpriteSP& sprite : _wrong_btns)
//  {
//    sprite = graphics::getSprite(_neutral_texture, btn_width, btn_height);
//    addDrawable(sprite);
//  }
//  utils::graphics::vAlign(_wrong_btns, (background_bounds.width / 6) * 4, btns_y, btns_total_height);
//  utils::graphics::hCircleAlign(_wrong_btns, -0.1 * background_bounds.width);

//  // Set sounds related to texture
//  _texture_sounds[&_error_texture]   = "hacking/error_step.wav";
//  _texture_sounds[&_success_texture] = "hacking/success_step.wav";
//  _texture_sounds[&_neutral_texture] = "hacking/neutral.wav";
//}

//events::EventAction Hacking::handleEvents(const sf::Event& event)
//{
//#pragma GCC diagnostic push
//#pragma GCC diagnostic ignored "-Wswitch"
//  switch(event.type)
//  {
//    case sf::Event::KeyPressed:
//    {
//      if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && _limitor.isAllow(sf::Keyboard::Left))
//      {
//        if(!rotate(Direction::Left))
//          return events::EventAction::ExitScreen;
//      }
//      else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && _limitor.isAllow(sf::Keyboard::Right))
//      {
//        if(!rotate(Direction::Right))
//          return events::EventAction::ExitScreen;
//      }
//      else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && _limitor.isAllow(sf::Keyboard::Space))
//      {
//        // \todo try answer
//      }
//      else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && _limitor.isAllow(sf::Keyboard::Escape))
//      {
//        return events::EventAction::ExitScreen;
//      }
//    }
//  }
//#pragma GCC diagnostic pop

//  return events::EventAction::Continue;
//}

//void Hacking::update(const sf::Time& elapsed_time)
//{
//  InteractibleScreen::update(elapsed_time);
//}

//bool Hacking::isReady() const noexcept
//{
//  return _intro_animation && _intro_animation->isFinished();
//}

//bool Hacking::rotate(Direction direction) noexcept
//{
//  if(!isReady())
//    return true;

//  _angle += direction == Direction::Left ? -ROTATION : ROTATION;

//  if(_angle > 360)
//    _angle -= 360;

//  _rotor->setRotation(_angle);
//  _failure_percentage += 1;

//  updateLevels();

//  if(_failure_percentage >= 100)
//    return false;

//  return true;
//}

//void Hacking::updateLevels() noexcept
//{
//  // Update errors
//  const size_t clean_until = NBR_BTNS - (_failure_percentage * NBR_BTNS / 100);
//  for(size_t i = 0; i < NBR_BTNS; ++i)
//  {
//    graphics::SpriteSP& sprite = _wrong_btns[i];
//    const sf::Texture& texture = i >= clean_until ? _error_texture : _neutral_texture;
//    setTexture(sprite, texture);
//  }

//  // Update success
//  const float proximity = std::abs(_target_angle - _angle);
//  const size_t neutral_until = (proximity * NBR_BTNS / 180);
////  std::cout << proximity << std::endl;
////  std::cout << neutral_until << std::endl;
//  for(size_t i = 0; i < NBR_BTNS; ++i)
//  {
//    graphics::SpriteSP& sprite = _right_btns[i];
//    const sf::Texture& texture = i > neutral_until ? _success_texture : _neutral_texture;
//    setTexture(sprite, texture);
//  }
//}

//void Hacking::setTexture(SpriteSP& sprite, const sf::Texture& texture) const noexcept
//{
//  if(sprite->getTexture() == &texture)
//    return;

//  sprite->setTexture(texture);

//  sound::SoundManager::play(_texture_sounds.at(&texture));
//}

//}
//}
