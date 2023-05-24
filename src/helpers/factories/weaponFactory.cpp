#include <entt/entity/registry.hpp>

#include "weaponFactory.h"
#include "../../comp/label.h"
#include "../../constants.h"
#include "../core/factories.h"
#include "../../comp/damage.h"
#include "../../comp/firerate.h"

entt::entity makeDesertEagle(entt::registry& reg) {
    const entt::entity e = makeWeapon(reg);
    reg.replace<Label>(e, WEAPON_LABEL_DEAGLE);
    reg.replace<FireRate>(e, WEAPON_FIRERATE_DEAGLE);
    reg.replace<Damage>(e, WEAPON_DAMAGE_DEAGLE);
    return e;
}