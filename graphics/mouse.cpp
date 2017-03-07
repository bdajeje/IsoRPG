#include "mouse.hpp"
#include "managers/texture_manager.hpp"
#include "managers/window.hpp"

namespace graphics {

namespace {
  std::string textureName(Mouse::Status status)
  {
    switch(status)
    {
      case Mouse::Status::Hover:
        return "mouse_hover.png";
      case Mouse::Status::Normal:
        return "mouse.png";
      case Mouse::Status::StartConversation:
        return "mouse_start_conversation.png";
      case Mouse::Status::Loot:
        return "mouse_loot.png";
      case Mouse::Status::ChangeMap:
        return "mouse_change_map.png";
    }
  }
}

std::shared_ptr<Mouse> Mouse::_instance;

void Mouse::init()
{
  _instance.reset(new Mouse());
}

Mouse::Mouse()
{
  mgr::Window::instance()->setMouseCursorVisible(false);
  const auto pos_x = mgr::Window::width() / 2;
  const auto pos_y = mgr::Window::height() / 2;
  sf::Mouse::setPosition(sf::Vector2i{pos_x, pos_y});
  _sprite = getSprite("mouse.png", 25, 25);
  _sprite->setPosition(pos_x, pos_y);
}

void Mouse::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  _sprite->draw(target, states);
}

void Mouse::setStatus(Status status) noexcept
{
  if(_instance->_status == status)
    return;

  _instance->_status = status;
  _instance->_sprite->setTexture(texture::TextureManager::get(textureName(status)), true);
}

}
