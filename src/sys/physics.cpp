#include <entt/entity/registry.hpp>
#include <qvector2d.h>

#include "physics.h"
#include "../comp/position.h"
#include "../comp/velocity.h"
#include "../comp/acceleration.h"
#include "../comp/player.h"
#include "../constants.h"
#include "../comp/enemy.h"

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

        if (reg.any_of<Player>(e)) {

            if (p.x() < 0.0f || p.x() > SCREEN_WIDTH) {
                p.setX(p.x() - REPULSION_COEFF * v.x());
                a *= ACCELERATION_LOSS;
            }

            if (p.y() < 0.0f || p.y() > SCREEN_HEIGHT) {
                p.setY(p.y() - REPULSION_COEFF * v.y());
                a *= ACCELERATION_LOSS;
            }

        }

        if (reg.any_of<Enemy>(e)) {

            if (p.x() < 0.0f || p.x() > SCREEN_WIDTH) {
                p.setX(p.x() - v.x());
                a.setX(-1.0f * a.x());
            }

            if (p.y() < 0.0f || p.y() > SCREEN_HEIGHT) {
                p.setY(p.y() - v.y());
                a.setX(-1.0f * a.x());
            }

        }
    }
}
