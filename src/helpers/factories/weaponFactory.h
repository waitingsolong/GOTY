#ifndef WEAPON_FACTORY_H
#define WEAPON_FACTORY_H

#include "../../core/game.h"
#include <entt/entity/fwd.hpp>

entt::entity makeDesertEagle(entt::registry&, Game*);

#endif // WEAPON_FACTORY_H