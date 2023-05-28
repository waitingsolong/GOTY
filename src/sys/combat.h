#ifndef COMBAT_H
#define COMBAT_H

#include <entt/entity/fwd.hpp>
#include "../core/game.h"

void startShoot(entt::registry& reg);

void stopShoot(entt::registry& reg);

void selectWeapon(entt::registry& reg, int key, Game* game);

void putOffWeapon(entt::registry& reg);

#endif //COMBAT_H