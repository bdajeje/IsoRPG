#include "mouse.hpp"
#include "managers/texture_manager.hpp"
#include "managers/window.hpp"

namespace graphics {

std::shared_ptr<Mouse> Mouse::_instance;

void Mouse::init()
{
  _instance.reset(new Mouse());
}

Mouse::Mouse()
{
  mgr::Window::instance()->setMouseCursorVisible(false);
  _sprite = getSprite("mouse.png", 25, 25);
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

  switch(status)
  {
    case Status::Hover:
      _instance->_sprite->setTexture(texture::TextureManager::get("mouse_hover.png"));
      break;
    case Status::Normal:
      _instance->_sprite->setTexture(texture::TextureManager::get("mouse.png"));
      break;
    case Status::StartConversation:
      _instance->_sprite->setTexture(texture::TextureManager::get("mouse_start_conversation.png"));
      break;
  }
}

}
