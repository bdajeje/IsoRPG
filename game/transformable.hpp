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

    void setScale(float factorX, float factorY) { _transformable->setScale(factorX, factorY); }
    virtual void setPosition(float x, float y) { _transformable->setPosition(x, y); }
    virtual void setPosition(const sf::Vector2f& position) { _transformable->setPosition(position); }
    void setRotation(float angle) { _transformable->setRotation(angle); }
    void setOrigin(float x, float y) { _transformable->setOrigin(x, y); }

    void move(float offsetX, float offsetY) { _transformable->move(offsetX, offsetY); }

  protected:

    std::shared_ptr<sf::Transformable> _transformable;
};

using TransformableSP = std::shared_ptr<game::Transformable>;

}

#endif // TRANSFORMABLE_HPP
