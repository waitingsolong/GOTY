#include <entt/entity/registry.hpp>
#include <qgraphicsitem.h>

#include "../../comp/player.h"
#include "../../comp/position.h"
#include "../../constants.h"
#include "../../comp/sprite.h"
#include "factories.h"
#include "../factories/weaponFactory.h"
#include "../../core/game.h"

void Game::equip(entt::registry& reg) {
    makeDesertEagle(reg, this);
}

void Game::setupPlayer(entt::registry& reg)
{
    makePlayer(reg);
    equip(reg);

    auto view = reg.view<Player, Position>();

    for (auto e : view) {
        auto& p = view.get<Position>(e).pos;
                   
        auto sprite = scene->addPixmap(PLAYER_SPRITE_DEFAULT);
        p.setX(PLAYER_SPAWNPOS.x() - sprite->boundingRect().width() / 2);
        p.setY(PLAYER_SPAWNPOS.y() - sprite->boundingRect().height() / 2);
        sprite->setShapeMode(QGraphicsPixmapItem::HeuristicMaskShape);
        sprite->setZValue(PLAYER_Z_VALUE);
        sprite->setPos(PLAYER_SPAWNPOS.x(), PLAYER_SPAWNPOS.y());

        reg.emplace<Sprite>(e, sprite);
    }
}
