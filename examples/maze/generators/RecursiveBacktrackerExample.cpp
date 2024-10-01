#include "../World.h"
#include "Random.h"
#include "RecursiveBacktrackerExample.h"
#include <climits>
bool RecursiveBacktrackerExample::Step(World* w) {
  // todo: implement this

  //Get the starting point as at the very corner of the maze
  auto sideOver2 = w->GetSize() / 2;
  if(stack.empty() && !visited[-sideOver2][-sideOver2]) {
    Point2D startPoint = Point2D(-sideOver2, -sideOver2);
    stack.push_back(startPoint);
    return true;
  }
  //If the stack is not empty then the maze is not yet done
  if(!stack.empty()) {
    Point2D point = stack.back();
    w->SetNodeColor(stack.back(), Color::Green);
    std::vector<Point2D> neighbors = getVisitables(w, point);
    visited[point.x][point.y] = true;
    //If all of the neighbors have been visited then we pop back to the last cell with uncarved walls
    if(neighbors.empty()) {
      w->SetNodeColor(point, Color::Black);
      stack.pop_back();
    }
    else {
      //If the neighbors have not been visited then we choose a random one
      int i = rand() % neighbors.size();

      if(neighbors[i].x > point.x) {
        w->SetEast(point, false);
        w->SetWest(neighbors[i], false);
      } else if(neighbors[i].x < point.x) {
        w->SetEast(neighbors[i], false);
        w->SetWest(point, false);
      } else if(neighbors[i].y > point.y) {
        w->SetNorth(neighbors[i], false);
        w->SetSouth(point, false);
      } else if(neighbors[i].y < point.y) {
        w->SetNorth(point, false);
        w->SetSouth(neighbors[i], false);
      }

      stack.push_back(neighbors[i]);
      w->SetNodeColor(neighbors[i], Color::Green);
    }
    return true;
  }

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
