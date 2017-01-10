#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <memory>

#include "utils/typedefs.hpp"
#include "utils/json.hpp"
#include "game/updatable.hpp"

namespace graphics {

class Animation : public game::Updatable
{
  public:

    Animation() = default;
    virtual ~Animation() = default;

    bool isFinished() const { return _finished; }
    virtual void finish() { _finished = true; }

  protected:

    bool _finished {false};    
};

using AnimationSP = std::shared_ptr<Animation>;

}

#endif // ANIMATION_HPP
