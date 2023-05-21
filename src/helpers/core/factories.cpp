#include "factories.h"

#include <entt/entity/registry.hpp>
#include <qgraphicsitem.h>

#include "../../constants.h"
#include "../../comp/player.h"
#include "../../comp/position.h"
#include "../../comp/life.h"
#include "../../comp/gore.h"
#include "../../comp/velocity.h"
#include "../../comp/acceleration.h"
#include "../../comp/hitbox.h"
#include "../../comp/sprite.h"

entt::entity makePlayer(entt::registry &reg) {
    const entt::entity e = reg.create();
    reg.emplace<Player>(e);
    reg.emplace<Position>(e, PLAYER_SPAWNPOINT);
    reg.emplace<Velocity>(e, QVector2D(0,0));
    reg.emplace<Acceleration>(e, QVector2D(0, 0));
    reg.emplace<Gore>(e, 0);
    reg.emplace<Life>(e, PLAYER_AMOUNT_OF_LIFES);
    //reg.emplace<Sprite>(e, QGraphicsPixmapItem(PLAYER_SPRITE_DEFAULT));
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
