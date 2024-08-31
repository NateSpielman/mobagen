#include "AlignmentRule.h"
#include "../gameobjects/Boid.h"

Vector2f AlignmentRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  // Try to match the heading of neighbors = Average velocity
  Vector2f averageVelocity = Vector2f::zero();

  // todo: add your code here to align each boid in a neighborhood
  // hint: iterate over the neighborhood
  if (!neighborhood.empty()) {
    Vector2f position = boid->transform.position;
    float countFlockmates = 0;
    for (int i = 0; i < neighborhood.size(); i++) {
      Boid* neighbor = neighborhood[i];
      averageVelocity += neighbor->velocity;
      countFlockmates++;
    }
    averageVelocity /= countFlockmates;
  }

  return Vector2f::normalized(averageVelocity);
}