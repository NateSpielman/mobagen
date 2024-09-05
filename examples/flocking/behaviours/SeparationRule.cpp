#include "SeparationRule.h"
#include "../gameobjects/Boid.h"
#include "../gameobjects/World.h"
#include "engine/Engine.h"

Vector2f SeparationRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  // Try to avoid boids too close
  Vector2f separatingForce = Vector2f::zero();
  float desiredDistance = desiredMinimalDistance;

  //    // todo: implement a force that if neighbor(s) enter the radius, moves the boid away from it/them
  if (!neighborhood.empty()) {
    Vector2f position = boid->transform.position;
    int countCloseFlockmates = 0;
    float closestDistance = desiredMinimalDistance;
  //    // todo: find and apply force only on the closest mates
    for (int i = 0; i < neighborhood.size(); i++) {
      Boid* neighbor = neighborhood[i];
      Vector2f neighborPosition = neighbor->transform.position;
      float distance = Vector2f::Distance(position, neighborPosition);
      if(closestDistance > distance) { closestDistance = distance; }
      if(distance < desiredDistance) {
        //Apply the inverse proportion of the distance between to the repulsive force
        Vector2f repulsiveForce = -(Vector2f::normalized(neighborPosition - position)/weight);
        separatingForce = separatingForce + repulsiveForce;
        countCloseFlockmates++;
      }
    }
    //use numbers between zero and one
    //divide by distance related to the radius
    separatingForce = Vector2f::normalized(separatingForce) / (closestDistance/desiredDistance);
  }

  return separatingForce;
}

bool SeparationRule::drawImguiRuleExtra() {
  ImGui::SetCurrentContext(world->engine->window->imGuiContext);
  bool valusHasChanged = false;

  if (ImGui::DragFloat("Desired Separation", &desiredMinimalDistance, 0.05f)) {
    valusHasChanged = true;
  }

  return valusHasChanged;
}
