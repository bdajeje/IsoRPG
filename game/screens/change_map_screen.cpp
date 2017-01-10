#include "change_map_screen.hpp"
#include "game/game.hpp"
#include "managers/window.hpp"

namespace game {
namespace screen {

ChangeMapScreen::ChangeMapScreen(const json& data)
  : _data {data}
{
  const auto window_size = mgr::Window::instance()->getSize();

  _background = std::make_shared<graphics::Rectangle>();
  auto& shape = _background->shape();
  shape->setFillColor(sf::Color(0, 0, 0, 0));
  shape->setSize(sf::Vector2f{window_size.x, window_size.y});
  _animation = std::make_shared<graphics::animations::FillColor>(shape, sf::Color::Black, sf::milliseconds(500));
  addDrawable(_background);
}

void ChangeMapScreen::update(const sf::Time& elapsed_time)
{
  if(_animation->isFinished())
  {
    if(_step == 1)
    {
      _step++;
      _animation = std::make_shared<graphics::animations::FillColor>(_background->shape(), sf::Color(0, 0, 0, 0), sf::milliseconds(500));
    }
    else
    {
      _finish = true;
      return;
    }
  }

  _animation->update(elapsed_time);

  if(_animation->isFinished())
  {
      const std::string& map_name = _data[0]["to_map"];
      Game::changeMap(map_name);
  }
}

}
}
