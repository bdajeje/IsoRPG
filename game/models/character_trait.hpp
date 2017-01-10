#ifndef CHARACTERTRAIT_HPP
#define CHARACTERTRAIT_HPP

#include <string>
#include <memory>

namespace game {

class CharacterTrait;
using CharacterTraitSP = std::shared_ptr<CharacterTrait>;

class CharacterTrait
{
  public:

    static CharacterTraitSP create(const std::string& name);

    const std::string& name() const noexcept { return _name; }

  protected:

    CharacterTrait(const std::string& name);

  private:

    std::string _name;
};

}

#endif // CHARACTERTRAIT_HPP
