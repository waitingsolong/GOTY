#include <entt/entity/registry.hpp>

#include "bulletFactory.h"
#include "../../comp/label.h"
#include "../../constants.h"
#include "../core/factories.h"
#include "../../comp/damage.h"
#include "../../comp/shotinterval.h"

//entt::entity makeDesertEagle(entt::registry& reg) {
//    const entt::entity e = makeWeapon(reg);
//    reg.replace<Label>(e, WEAPON_LABEL_DEAGLE);
//    reg.replace<ShotInterval>(e, WEAPON_SHOT_INTERVAL_DEAGLE);
//    reg.replace<Damage>(e, WEAPON_DAMAGE_DEAGLE);
//    return e;
//}