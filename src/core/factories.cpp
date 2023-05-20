#include "factories.h"

#include <entt/entity/registry.hpp>

entt::entity makePlayer(entt::registry &reg) {
//    const entt::entity e = reg.create();
//    reg.emplace<Player>(e);
//    reg.emplace<DesiredDir>(e, playerSpawnDir);
//    reg.emplace<ActualDir>(e, playerSpawnDir);
//    reg.emplace<Position>(e, playerSpawnPos);
//    reg.emplace<PlayerSprite>(e, animera::SpriteID::pacman_beg_);
    return e;
}

entt::entity makeBullet(entt::registry &reg) {
    const entt::entity e = reg.create();
//    reg.emplace<Player>(e);
//    reg.emplace<DesiredDir>(e, playerSpawnDir);
//    reg.emplace<ActualDir>(e, playerSpawnDir);
//    reg.emplace<Position>(e, playerSpawnPos);
//    reg.emplace<PlayerSprite>(e, animera::SpriteID::pacman_beg_);
    return e;
}
