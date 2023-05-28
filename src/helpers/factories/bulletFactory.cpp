#include <entt/entity/registry.hpp>

#include "bulletFactory.h"
#include "../../comp/label.h"
#include "../../constants.h"
#include "../core/factories.h"
#include "../../comp/damage.h"

entt::entity makeBulletDefault(entt::registry& reg) {
    const entt::entity e = makeBullet(reg);

    return e;
}