#ifndef MAXED_VALUE_HPP
#define MAXED_VALUE_HPP

template <class T>
class MaxedValue
{
  public:

    MaxedValue() = default;
    MaxedValue(T value, T max)
      : _value {value}
      , _max {max}
    {}

    T _value;
    T _max;
};

#endif // MAXED_VALUE_HPP
