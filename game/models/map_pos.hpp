#ifndef MAP_POS_HPP
#define MAP_POS_HPP

struct MapPos {
  MapPos() = default;

  MapPos(int x, int y)
    : x {x}
    , y {y}
  {}

  MapPos(const MapPos& map_pos)
    : x {map_pos.x}
    , y {map_pos.y}
  {}

  bool operator==(const MapPos& map_pos) const
  {
    return x == map_pos.x && y == map_pos.y;
  }

  bool operator!=(const MapPos& map_pos) const
  {
    return x != map_pos.x || y != map_pos.y;
  }

  int x {0};
  int y {0};
};

enum class Direction { TopLeft, TopRight, BottomLeft, BottomRight };

Direction getDirection(const MapPos& pos_a, const MapPos& pos_b);

#endif // MAP_POS_HPP
