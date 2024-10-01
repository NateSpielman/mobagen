#include "../World.h"
#include "Random.h"
#include "RecursiveBacktrackerExample.h"
#include <climits>
bool RecursiveBacktrackerExample::Step(World* w) {
  // todo: implement this
  return false;
}

void RecursiveBacktrackerExample::Clear(World* world) {
  visited.clear();
  stack.clear();
  auto sideOver2 = world->GetSize() / 2;

  for (int i = -sideOver2; i <= sideOver2; i++) {
    for (int j = -sideOver2; j <= sideOver2; j++) {
      visited[i][j] = false;
    }
  }
}

Point2D RecursiveBacktrackerExample::randomStartPoint(World* world) {
  auto sideOver2 = world->GetSize() / 2;

  // todo: change this if you want
  for (int y = -sideOver2; y <= sideOver2; y++)
    for (int x = -sideOver2; x <= sideOver2; x++)
      if (!visited[y][x]) return {x, y};
  return {INT_MAX, INT_MAX};
}

std::vector<Point2D> RecursiveBacktrackerExample::getVisitables(World* w, const Point2D& p) {
  auto sideOver2 = w->GetSize() / 2;
  std::vector<Point2D> visitables;

  // todo: implement this
  //If we have not visited the left of the current point and it doesn't go out of bounds we add it to the stack
  //When checking we only need to get the x position of the left point because it will have the same y as our current point
  if(!visited[p.Left().x][p.y] && p.Left().x > -sideOver2-1) {
    visitables.push_back(p.Left());
  }
  //We do a similar check for the right point, if we haven't visited it then push it to the stack
  //Once again we only need to get the x position because it's on the same y
  if(!visited[p.Right().x][p.y] && p.Right().x < sideOver2+1) {
    visitables.push_back(p.Right());
  }
  //If we haven't visited the up point and it's in bounds we push it to the stack
  if(!visited[p.x][p.Up().y] && p.Up().y > -sideOver2-1) {
    visitables.push_back(p.Up());
  }
  //Lastly check the down point like we've been doing for all the other
  if(!visited[p.x][p.Down().y] && p.Down().y < sideOver2+1) {
    visitables.push_back(p.Down());
  }

  return visitables;
}
