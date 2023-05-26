#include <entt/entity/registry.hpp>

#include "combat.h"
#include "../comp/weapon.h"
#include "../comp/timer.h"

// DEBUG
#include <qdebug.h>

// shoot must be here R.I.P.

void startShoot(entt::registry& reg) {
    qDebug() << "start shooting";

    auto view = reg.view<Weapon, Timer>();

    for (auto e : view) {
        if (!view.get<Weapon>(e).curr) {
            continue; 
        };

        auto t = view.get<Timer>(e).t;

        t->start(); 
    }
}

void stopShoot(entt::registry& reg) {
    qDebug() << "stop shooting";

    auto view = reg.view<Weapon, Timer>();

    for (auto e : view) {
        if (!view.get<Weapon>(e).curr) {
            continue;
        };

        auto t = view.get<Timer>(e).t;

        t->stop();
    }
}
