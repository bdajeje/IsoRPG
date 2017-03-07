#ifndef KEYLIMITOR_HPP
#define KEYLIMITOR_HPP

#include <memory>

#include <SFML/Window/Keyboard.hpp>

#include "utils/timer.hpp"

namespace utils {

/*! Limit key repeat */
class KeyLimitor
{
  public:

    static void init(sf::Int32 min_elapsed_time);
    static std::shared_ptr<KeyLimitor>& instance() { return _instance; }

    /*! Constructor
     *  \param min_elapsed_time - milliseconds
     */
    KeyLimitor( sf::Int32 min_elapsed_time );

    static bool isAllow( sf::Keyboard::Key key );

  private:

    time::Timer _timer;
    const sf::Int32 _min_elapsed_time; // milliseconds
    sf::Keyboard::Key _last_checked_key {sf::Keyboard::Key::Unknown};
    static std::shared_ptr<KeyLimitor> _instance;
};

}

#endif // KEYLIMITOR_HPP
