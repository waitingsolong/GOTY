#ifndef PHYSICS_H
#define PHYSICS_H

#include <entt/entity/fwd.hpp>

void updatePhysics(entt::registry& reg);

void moveAll(entt::registry& reg);
void collideAll(entt::registry& reg);

#endif //PHYSICS_H