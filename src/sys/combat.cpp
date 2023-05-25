#include <entt/entity/registry.hpp>

#include "combat.h"
#include "../comp/weapon.h"
#include "../comp/timer.h"

// shoot must be here R.I.P.

void startShoot(entt::registry& reg) {
    auto view = reg.view<Weapon, Timer>();

    for (auto e : view) {
        auto t = view.get<Timer>(e).t;

        t->start(); 
    }
}

void stopShoot(entt::registry& reg) {
    auto view = reg.view<Weapon, Timer>();

    for (auto e : view) {
        auto t = view.get<Timer>(e).t;

        t->stop();
    }
}
