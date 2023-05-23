#include <entt/entity/registry.hpp>
#include <qgraphicsitem.h>

#include "setupplayer.h"
#include "../../comp/player.h"
#include "../../comp/position.h"
#include "../../constants.h"
#include "../../comp/sprite.h"
#include "factories.h"

void setupPlayer(entt::registry& reg, QGraphicsScene* scene)
{
    makePlayer(reg);

    auto view = reg.view<Player, Position>();

    for (auto e : view) {
        const auto& p = view.get<Position>(e).pos;
                   
        auto sprite = scene->addPixmap(PLAYER_SPRITE_DEFAULT);
        sprite->setZValue(PLAYER_Z_VALUE);
        sprite->setPos(PLAYER_SPAWNPOS.x(), PLAYER_SPAWNPOS.y());

        reg.emplace<Sprite>(e, sprite);
    }
}
