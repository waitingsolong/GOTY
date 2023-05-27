#include <entt/entity/registry.hpp>

#include "weaponFactory.h"
#include "../../comp/label.h"
#include "../../constants.h"
#include "../core/factories.h"
#include "../../comp/damage.h"
#include "../../comp/timer.h"
#include "../../comp/weapon.h"

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

    //auto view = reg.view<Player, Position>();

    //for (auto e : view) {
    //    auto& p = view.get<Position>(e).pos;

    //    auto sprite = scene->addPixmap(PLAYER_SPRITE_DEFAULT);
    //    p.setX(PLAYER_SPAWNPOS.x() - sprite->boundingRect().width() / 2);
    //    p.setY(PLAYER_SPAWNPOS.y() - sprite->boundingRect().height() / 2);
    //    sprite->setShapeMode(QGraphicsPixmapItem::HeuristicMaskShape);
    //    sprite->setZValue(PLAYER_Z_VALUE);
    //    sprite->setPos(PLAYER_SPAWNPOS.x(), PLAYER_SPAWNPOS.y());

    //    reg.emplace<Sprite>(e, sprite);
    //}
    
    return e;
}