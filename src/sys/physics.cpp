#include <entt/entity/registry.hpp>
#include <qvector2d.h>

#include "physics.h"
#include "../comp/position.h"
#include "../comp/velocity.h"
#include "../comp/acceleration.h"
#include "../comp/player.h"
#include "../constants.h"
#include "../comp/enemy.h"

// DEBUG
#include <iostream>

void updatePhysics(entt::registry& reg)
{
    moveAll(reg);
    collideAll(reg);
}

void moveAll(entt::registry& reg)
{
    auto view = reg.view<Position, Velocity, Acceleration>();

    for (auto e : view) {
        auto& p = view.get<Position>(e).pos;
        auto& v = view.get<Velocity>(e).vel;
        auto& a = view.get<Acceleration>(e).acc;

        p += v;
        v += a; 

        //std::cout << "\na: " << a.x() << " " << a.y();
        //std::cout << "\nv: " << v.x() << " " << v.y();
        //std::cout << "\np: " << p.x() << " " << p.y();
    }
}

void collideAll(entt::registry& reg)
{
    auto view = reg.view<Position, Velocity, Acceleration>();

    QVector2D p;
    QVector2D v;
    QVector2D a;
    for (auto e : view) {
        auto& p = view.get<Position>(e).pos;
        auto& v = view.get<Velocity>(e).vel;
        auto& a = view.get<Acceleration>(e).acc;

        if (p.x() < 0.0f || p.x() > SCREEN_WIDTH) {
            v.setX(-1.0f * v.x());
            a.setX(-1.0f * a.x());
            v *= VELOCITY_LOSS_COEFF;
            a *= ACCELERATION_LOSS_COEFF;
            p.setX(p.x() + v.x());
        }

        if (p.y() < 0.0f || p.y() > SCREEN_HEIGHT) {
            v.setY(-1.0f * v.y());
            a.setY(-1.0f * a.y());
            v *= VELOCITY_LOSS_COEFF;
            a *= ACCELERATION_LOSS_COEFF;
            p.setY(p.y() + v.y());
        }

    }
}
