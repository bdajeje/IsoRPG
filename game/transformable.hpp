#ifndef TRANSFORMABLE_HPP
#define TRANSFORMABLE_HPP

#include <memory>
#include <SFML/Graphics/Transformable.hpp>

namespace game {

class Transformable
{
  public:

    Transformable();
    Transformable(std::shared_ptr<sf::Transformable>& transformable);
    virtual ~Transformable() = default;

    virtual const sf::Vector2f& getPosition() const { return _transformable->getPosition(); }

    virtual void setScale(float factorX, float factorY) { _transformable->setScale(factorX, factorY); }
    virtual void setPosition(float x, float y) { _transformable->setPosition(x, y); }
    void setPosition(const sf::Vector2f& position) { setPosition(position.x, position.y); }
    virtual void setRotation(float angle) { _transformable->setRotation(angle); }
    virtual void setOrigin(float x, float y) { _transformable->setOrigin(x, y); }

    virtual void move(float offsetX, float offsetY) { _transformable->move(offsetX, offsetY); }

    std::shared_ptr<sf::Transformable>& transformable() { return _transformable; }

  protected:

    std::shared_ptr<sf::Transformable> _transformable;
};

using TransformableSP = std::shared_ptr<game::Transformable>;

}

#endif // TRANSFORMABLE_HPP
