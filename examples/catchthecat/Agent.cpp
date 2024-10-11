#include "Agent.h"
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include "World.h"
using namespace std;

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
  int distanceTo(const Point2D &other) const {
    return abs(point.x - other.x) + abs(point.y - other.y);
  }
};

std::vector<Point2D> Agent::generatePath(World* w) {
  unordered_map<Point2D, Point2D> cameFrom;  // to build the flowfield and build the path
  priority_queue<ASNode> frontier;                   // to store next ones to visit
  unordered_set<Point2D> frontierSet;        // OPTIMIZATION to check faster if a point is in the queue
  unordered_map<Point2D, bool> visited;      // use .at() to get data, if the element dont exist [] will give you wrong results

  auto sideSizeOver2 = w->getWorldSideSize() / 2;
  // bootstrap state
  auto catPos = w->getCat();
  frontier.push({catPos,0, distanceToBorder(catPos, sideSizeOver2)});
  frontierSet.insert(catPos);
  Point2D borderExit = Point2D::INFINITE;  // if at the end of the loop we dont find a border, we have to return random points

  while (!frontier.empty()) {
    // get the current from frontier
    ASNode node = frontier.top();

    // remove the current from frontierset
    frontier.pop();
    frontierSet.erase(node.point);

    // mark current as visited
    visited[node.point] = true;

    // getVisitableNeightbors(world, current) returns a vector of neighbors that are not visited, not cat, not block, not in the queue
    vector<Point2D> visitableNeighbors = getVisitableNeighbors(w, node.point);
    // iterate over the neighs:
    // for every neighbor set the cameFrom
    // enqueue the neighbors to frontier and frontierset
    // do this up to find a visitable border and break the loop
  }

  // if the border is not infinity, build the path from border to the cat using the camefrom map
  // if there isnt a reachable border, just return empty vector
  // if your vector is filled from the border to the cat, the first element is the catcher move, and the last element is the cat move
  return vector<Point2D>();
}

vector<Point2D> getVisitableNeighbors(World* w, const Point2D& p) {
  vector<Point2D> neighbors = World::neighbors(p);

}
