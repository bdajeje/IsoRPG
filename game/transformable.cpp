#include "transformable.hpp"

namespace game {

Transformable::Transformable()
{

}

Transformable::Transformable(std::shared_ptr<sf::Transformable>& transformable)
  : _transformable {transformable}
{

}

}
