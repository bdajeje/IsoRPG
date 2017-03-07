#ifndef MOUSE_HPP
#define MOUSE_HPP

#include "graphics/sprite.hpp"

namespace graphics {

class Mouse final : public sf::Drawable
{
  public:

    enum class Status {
      Normal, Hover, StartConversation, ChangeMap, Loot
    };

    static void init();
    static std::shared_ptr<Mouse>& instance() { return _instance; }
    static void setStatus(Status status) noexcept;
    static void updatePos(size_t x, size_t y) noexcept { _instance->_sprite->setPosition(x, y); }

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

  private:

    Mouse();    

  private:

    SpriteSP _sprite;
    Status _status;
    static std::shared_ptr<Mouse> _instance;
};

}

#endif // MOUSE_HPP
