#ifndef BOUNDEDNUMBER_HPP
#define BOUNDEDNUMBER_HPP

template <class T>
class BoundedNumber
{
  public:

    BoundedNumber(T min, T max, T value = 0)
      : _min {min}
      , _max {max}
      , _value {value}
    {}

    void operator++()
    {
      if(_value == _max)
        _value = _min;
      else
        _value++;
    }

    void operator--()
    {
      if(_value == _min)
        _value = _max;
      else
        _value--;
    }

  private:

    T _min;
    T _max;
    T _value;
};

#endif // BOUNDEDNUMBER_HPP
