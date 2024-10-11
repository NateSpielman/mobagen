#ifndef AGENT_H
#define AGENT_H
#include "math/Point2D.h"
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <queue>

class World;

struct ASNode {
  Point2D point;
  int accDistance;
  int heuristicDistance;
  //Operator < used to compare two nodes
  //We want to know if the node we're comparing has a smaller value
  bool operator<(const ASNode& rhs) const {
    return (accDistance + heuristicDistance) > (rhs.accDistance + heuristicDistance);
  }
  //manhattan distance
  int distanceToPoint(const Point2D &other) const {
    return abs(point.x - other.x) + abs(point.y - other.y);
  }
};

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
private:
  std::priority_queue<ASNode> frontier;           // to store next ones to visit
  std::unordered_set<Point2D> frontierSet;        // OPTIMIZATION to check faster if a point is in the queue
  std::unordered_map<Point2D, bool> visited;      // use .at() to get data, if the element dont exist [] will give you wrong results
public:
  explicit Agent() = default;

  virtual Point2D Move(World*) = 0;

  std::vector<Point2D> generatePath(World* w);
  std::vector<Point2D> getVisitableNeighbors(World* w, const Point2D& p);
};

#endif  // AGENT_H
