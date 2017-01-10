#include "map_pos.hpp"

Direction getDirection(const MapPos& pos_a, const MapPos& pos_b)
{
  if(pos_a.x < pos_b.x)
    return Direction::BottomRight;
  else if(pos_a.x > pos_b.x)
    return Direction::TopLeft;
  else if(pos_a.y < pos_b.y)
    return Direction::BottomLeft;
  else
    return Direction::TopRight;
}
