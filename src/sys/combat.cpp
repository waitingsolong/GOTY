#include <entt/entity/registry.hpp>

// DEBUG
#include <qdebug.h>

#include "combat.h"
#include "../comp/weapon.h"
#include "../comp/timer.h"
#include "../comp/label.h"
#include "../comp/sprite.h"
#include "../comp/player.h"
#include "../comp/position.h"
#include "../comp/damage.h"
#include "../comp/velocity.h"
#include "../comp/acceleration.h"
#include "../helpers/core/factories.h"
#include "../assets.h"

// shoot must be here R.I.P.

void startShoot(entt::registry& reg) {
    auto view = reg.view<Weapon, Timer>();

    for (auto e : view) {
        if (!view.get<Weapon>(e).curr) {
            continue; 
        };

        auto t = view.get<Timer>(e).t;

        t->start(); 

        // first shoot 
        QMetaObject::invokeMethod(t, "timeout");

        break;
    }
}

void stopShoot(entt::registry& reg) {
    auto view = reg.view<Weapon, Timer>();

    for (auto e : view) {
        if (!view.get<Weapon>(e).curr) {
            continue;
        };

        auto t = view.get<Timer>(e).t;

        t->stop();

        break; 
    }
}

inline constexpr float BULLET_ACCEL_MAG = 0.0f; 
inline constexpr float BULLET_VEL_MAG = 3.0f;

void Game::shoot() {
    // somewhere will be info about bullets type 

    QPointF dest = this->mapFromGlobal(QCursor::pos());

    auto be = makeBullet(reg);
    auto viewWeapon = reg.view<Weapon, Damage, Label>();
    auto viewPlayer = reg.view<Player, Position, Velocity, Acceleration>();

    // get physics from player
    
    QVector2D pos; 
    for (auto pe : viewPlayer) {
        auto& p = viewPlayer.get<Position>(pe).pos;

        reg.replace<Velocity>(be, viewPlayer.get<Velocity>(pe).vel);
        reg.replace<Acceleration>(be, viewPlayer.get<Acceleration>(pe).acc);
        pos = viewPlayer.get<Position>(pe).pos;
        reg.replace<Position>(be, pos);
    }

    QVector2D vec = (pos - QVector2D(dest)).normalized(); // vector from dest to source point 
    reg.get<Acceleration>(be).acc += vec * BULLET_ACCEL_MAG; // drag force 
    auto& vel = reg.get<Velocity>(be).vel; 
    vel += (-vec) * BULLET_VEL_MAG; // bullet muzzle velocity 

    // get stats from weapon 

    for (auto we : viewWeapon) {
        if (!viewWeapon.get<Weapon>(we).curr) {
            continue;
        }
        
        reg.replace<Damage>(be, viewWeapon.get<Damage>(we).d);

        QGraphicsPixmapItem* sprite; 
        if (viewWeapon.get<Label>(we).l == WEAPON_LABEL_DEAGLE) {
            //// DEBUG
            //qDebug() << vel.x() << ' ' << vel.y() << ' ' << qRadiansToDegrees(qAtan2(vel.y(), vel.x())) << ' ' <<
            //                                                qRadiansToDegrees(static_cast<float>(getNearestAngle(vel)) / 10.0f);
            qDebug() << "idinahui";
            sprite = scene->addPixmap(getNearestPixmap(vel, BULLET_LABEL_50AE)); // (!) later check what type of ammo using right now
        }

        sprite->setShapeMode(QGraphicsPixmapItem::HeuristicMaskShape);

        reg.emplace<Sprite>(be, sprite);
    }
}

void selectWeapon(entt::registry& reg, int key, Game* view) {
    auto viewWeapon = reg.view<Weapon, Label, Sprite>();

    for (auto e : viewWeapon) {
        auto& l = viewWeapon.get<Label>(e).l;
        if (l == key && !viewWeapon.get<Weapon>(e).curr) {
            viewWeapon.get<Weapon>(e).curr = true;

            auto& sprite = viewWeapon.get<Sprite>(e).sp;
            sprite->setVisible(true);

            break; 
        }
    }
}

void putOffWeapon(entt::registry& reg) {
    auto viewWeapon = reg.view<Weapon, Sprite>();

    for (auto e : viewWeapon) {
        if (viewWeapon.get<Weapon>(e).curr) {
            viewWeapon.get<Weapon>(e).curr = false;

            auto& sprite = viewWeapon.get<Sprite>(e).sp;
            sprite->setVisible(false);

            break; 
        }
    }
}
