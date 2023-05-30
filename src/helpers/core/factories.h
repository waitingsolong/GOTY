#ifndef FACTORIES_H
#define FACTORIES_H

#include <entt/entity/fwd.hpp>

entt::entity makePlayer(entt::registry &);
entt::entity makeEnemy(entt::registry &);
entt::entity makeBullet(entt::registry &);
entt::entity makeWeapon(entt::registry&);
entt::entity makeBoss(entt::registry&);

#endif // FACTORIES_H
