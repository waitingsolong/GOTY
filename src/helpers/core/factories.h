#ifndef FACTORIES_H
#define FACTORIES_H

#include <entt/entity/fwd.hpp>

entt::entity makePlayer(entt::registry &);
entt::entity makeBullet(entt::registry &);

#endif // FACTORIES_H
