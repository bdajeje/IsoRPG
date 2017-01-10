#ifndef SERIALIZABLE_HPP
#define SERIALIZABLE_HPP

#include "utils/json.hpp"

namespace utils {

class Serializable
{
  public:

//    Serializable(const json& data);
    Serializable();
    virtual ~Serializable() = default;

    virtual json save() = 0;
//    const json& data() const noexcept { return _data; }

//  protected:

//    json _data;
};

}

#endif // SERIALIZABLE_HPP
