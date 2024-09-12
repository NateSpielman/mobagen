#include "JohnConway.h"

// Reference: https://playgameoflife.com/info
void JohnConway::Step(World& world) {
  //Go through all the columns and lines
  for(int c = 0; c < world.SideSize(); c++) {
    for(int l = 0; l < world.SideSize(); l++) {
      //Get the amount of neighbors for the point at position C L
      int neighborCount = CountNeighbors(world, {c,l});
      bool isAlive = world.Get({c,l});
      //If the point at C L has less than 2 neighbors and is alive then it dies
      if(neighborCount < 2 && isAlive) {
        world.SetNext({c, l}, false);
      }
      //If the point at C L has 2 or 3 neighbors and is alive then it stays alive
      else if((neighborCount == 2 || neighborCount == 3) && isAlive) {
        world.SetNext({c, l}, true);
      }
      //If the point at C L has more than three neighbors and is alive then it dies
      else if(neighborCount > 3 && isAlive) {
        world.SetNext({c, l}, false);
      }
      //If the point at C L has exactly 3 neighbors and is not alive then it becomes alive
      else if(neighborCount == 3 && isAlive == false) {
        world.SetNext({c, l}, true);
      }
    }
  }

}

int JohnConway::CountNeighbors(World& world, Point2D point) {
  int count = 0;
  for(int y=-1; y<=1; y++) {
    for(int x=-1; x<=1; x++) {
      Point2D p = Point2D(point.x + x, point.y + y);
      //Do not count self
      if(x == 0 && y == 0) {
      } else {
        count += world.Get(p);
      }
    }
  }
  return count;
}
