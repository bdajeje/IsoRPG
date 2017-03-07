#ifndef UTILS_RANDOM_HPP
#define UTILS_RANDOM_HPP

#include <stdlib.h>

namespace utils {

static int random(int min, int max)
{
  if(min == max)
    return min;

  return rand() % max + min;
}

}

#endif // UTILS_RANDOM_HPP
