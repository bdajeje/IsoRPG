#ifndef UPDATABLE_HPP
#define UPDATABLE_HPP

#include <SFML/System/Time.hpp>

namespace game {

class Updatable
{
  public:

    virtual void update(const sf::Time& time) = 0;
};

}

#endif // UPDATABLE_HPP
