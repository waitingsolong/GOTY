#include "factories.h"

#include <entt/entity/registry.hpp>

#include "../../constants.h"
#include "../../comp/player.h"
#include "../../comp/position.h"
#include "../../comp/life.h"
#include "../../comp/gore.h"
#include "../../comp/velocity.h"
#include "../../comp/acceleration.h"
#include "../../comp/spritevector.h"
#include "../../comp/weapon.h"
#include "../../comp/label.h"
#include "../../comp/damage.h"
#include "../../comp/firerate.h"

entt::entity makePlayer(entt::registry &reg) {
    const entt::entity e = reg.create();
    reg.emplace<Player>(e);
    reg.emplace<Position>(e);
    reg.emplace<Velocity>(e, NULL_VECTOR);
    reg.emplace<Acceleration>(e, NULL_VECTOR);
    reg.emplace<Gore>(e, 0);
    reg.emplace<Life>(e, PLAYER_AMOUNT_OF_LIFES);
    return e;
}

// 1) should bool cur stay in Weapon comp. 
// 2) how to aggregate weapons to player 

entt::entity makeWeapon(entt::registry& reg) {
    const entt::entity e = reg.create();
    reg.emplace<Weapon>(e);
    reg.emplace<Label>(e);
    reg.emplace<Damage>(e);
    reg.emplace<FireRate>(e);
    return e;
}

entt::entity makeEnemy(entt::registry& reg) {
    const entt::entity e = reg.create();

    return e;
}

entt::entity makeBoss(entt::registry& reg) {
    const entt::entity e = reg.create();

    return e;
}

entt::entity makeBullet(entt::registry &reg) {
    const entt::entity e = reg.create();
    
    return e;
}
