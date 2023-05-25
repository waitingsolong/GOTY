#include <entt/entity/registry.hpp>

#include "weaponFactory.h"
#include "../../comp/label.h"
#include "../../constants.h"
#include "../core/factories.h"
#include "../../comp/damage.h"
#include "../../comp/shotinterval.h"
#include "../../comp/timer.h"

entt::entity makeAutoWeapon(entt::registry& reg) {
    const entt::entity e = makeWeapon(reg);
    reg.emplace<Timer>(e);
    reg.patch<Timer>(e, new QTimer());
    return e;
}

entt::entity makeDesertEagle(entt::registry& reg, Game* game) {
    const entt::entity e = makeAutoWeapon(reg);
    reg.replace<Label>(e, WEAPON_LABEL_DEAGLE);
    reg.replace<Damage>(e, WEAPON_DAMAGE_DEAGLE);
    //reg.patch<Timer>(e, [&](QTimer* t) { t->setInterval(WEAPON_SHOT_INTERVAL_DEAGLE); 
    //                                    QObject::connect(t, SIGNAL(timeout()), game, SLOT(shoot())); } );

    return e;
}