#include "Agent.h"
#include "World.h"

#include <algorithm>
#include <ranges>
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
  int distanceToPoint(const Point2D &other) const {
    return abs(point.x - other.x) + abs(point.y - other.y);
  }
};

std::vector<Point2D> Agent::generatePath(World* w) {
  std::priority_queue<ASNode> frontier;           // to store next ones to visit
  std::unordered_set<Point2D> frontierSet;        // OPTIMIZATION to check faster if a point is in the queue
  std::unordered_map<Point2D, bool> visited;      // use .at() to get data, if the element dont exist [] will give you wrong results
  unordered_map<Point2D, Point2D> cameFrom;  // to build the flowfield and build the path

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

    // do this up to find a visitable border and break the loop
    if(abs(node.point.x) == sideSizeOver2 || abs(node.point.y) == sideSizeOver2) {
      borderExit = node.point;
      break;
    }

    // getVisitableNeightbors(world, current) returns a vector of neighbors that are not visited, not cat, not block, not in the queue
    vector<Point2D> neighbors = World::neighbors(node.point);
    vector<Point2D> visitableNeighbors = vector<Point2D>();

    for(auto neighbor : neighbors) {
      //Check that neighbor is not blocked or the cat position and is valid
      if(!w->getContent(neighbor) && neighbor != w->getCat() && w->isValidPosition(neighbor)) {
        //Push back the neighbor if they are not visited or in the queue
        if(!visited.contains(neighbor) && !frontierSet.contains(neighbor)) {
          visitableNeighbors.push_back(neighbor);
        }
      }
    }
    
    // iterate over the neighs:
    for (auto neighbor : visitableNeighbors) {
      // for every neighbor set the cameFrom
      ASNode neighborNode;
      neighborNode.point = neighbor;
      neighborNode.heuristicDistance = distanceToBorder(neighborNode.point, sideSizeOver2);
      neighborNode.accDistance = node.accDistance + 1;
      cameFrom[neighborNode.point] = node.point;
      // enqueue the neighbors to frontier and frontierset
      frontier.push(neighborNode);
      frontierSet.insert(neighborNode.point);
    }
  }

  // if the border is not infinity, build the path from border to the cat using the camefrom map
  vector<Point2D> path;
  if(borderExit != Point2D::INFINITE) {
    Point2D currentPoint = borderExit;
    while(currentPoint != catPos) {
      path.push_back(currentPoint);
      currentPoint = cameFrom[currentPoint];
    }
    return path;
  }
  // if there isn't a reachable border, just return empty vector
  // if your vector is filled from the border to the cat, the first element is the catcher move, and the last element is the cat move
  return vector<Point2D>();
}
