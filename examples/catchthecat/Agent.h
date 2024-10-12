#ifndef AGENT_H
#define AGENT_H
#include "math/Point2D.h"
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <queue>

class World;

static int distanceToBorder(const Point2D &p, int sideSizeOver2) {
  //right
  if(p.y - p.x < 0 && p.x + p.y > 0) {
    return sideSizeOver2 - p.x;
  }
  //Top
  if(p.x - p.y < 0 && p.x + p.y > 0) {
    return sideSizeOver2 - p.y;
  }
  //Left
  if(p.x - p.y < 0 && p.x + p.y < 0) {
    return sideSizeOver2 - abs(p.x);
  }
  //Bottom
  if(p.x - p.y > 0 && p.x + p.y < 0) {
    return sideSizeOver2 - abs(p.y);
  }

  //(0,0)
  return sideSizeOver2;
}

class Agent {
public:
  explicit Agent() = default;

  virtual Point2D Move(World*) = 0;

  std::vector<Point2D> generatePath(World* w);
};

#endif  // AGENT_H
