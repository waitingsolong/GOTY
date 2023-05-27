#include <entt/entity/registry.hpp>

#include "weaponFactory.h"
#include "../../comp/label.h"
#include "../../constants.h"
#include "../core/factories.h"
#include "../../comp/damage.h"
#include "../../comp/timer.h"
#include "../../comp/weapon.h"
#include "../../comp/sprite.h"
#include "../../comp/player.h"
#include "../../comp/spriteGroup.h"

entt::entity makeAutoWeapon(entt::registry& reg) {
    const entt::entity e = makeWeapon(reg);
    reg.emplace<Timer>(e);
    return e;
}

entt::entity makeDesertEagle(entt::registry& reg, Game* game) {
    const entt::entity e = makeAutoWeapon(reg);
    reg.replace<Label>(e, WEAPON_LABEL_DEAGLE);
    reg.replace<Damage>(e, WEAPON_DAMAGE_DEAGLE);
    reg.replace<Weapon>(e, false);

    QTimer* t = new QTimer();
    t->setInterval(WEAPON_SHOT_INTERVAL_DEAGLE);
    QObject::connect(t, &QTimer::timeout, game, &Game::shoot);
    reg.replace<Timer>(e, t);
    
    //

    auto view = reg.view<Player, SpriteGroup>();
    QGraphicsItemGroup* playerGroup;

    for (auto e : view) {
        auto sprite = game->scene->addPixmap(WEAPON_SPRITE_DEAGLE);
        sprite->setPos(PLAYER_SPAWNPOS.x() + 37, PLAYER_SPAWNPOS.y() - 5); // MAGIC

        playerGroup = view.get<SpriteGroup>(e).gr;
        playerGroup->addToGroup(sprite);
    }
    
    return e;
}