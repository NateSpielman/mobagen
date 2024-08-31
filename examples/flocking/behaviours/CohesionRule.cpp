#include "CohesionRule.h"
#include "../gameobjects/Boid.h"

Vector2f CohesionRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  Vector2f cohesionForce;

  // todo: add your code here to make a force towards the center of mass
  // hint: iterate over the neighborhood
  if (!neighborhood.empty()) {
    Vector2f position = boid->transform.position;
    Vector2f centerOfMass;
    float countFlockmates = 0;
    for (int i = 0; i < neighborhood.size(); i++) {
      Boid* neighbor = neighborhood[i];
      Vector2f neighborPosition = neighbor->transform.position;
      centerOfMass = centerOfMass + neighborPosition;
      countFlockmates++;
    }
    // find center of mass
    centerOfMass = centerOfMass / countFlockmates;
    cohesionForce = centerOfMass - position;
  }

  cohesionForce = Vector2f::normalized(cohesionForce);

  return cohesionForce;
}