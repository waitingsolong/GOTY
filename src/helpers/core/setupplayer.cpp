#include <entt/entity/registry.hpp>
#include <qgraphicsitem.h>

#include "../../comp/player.h"
#include "../../comp/position.h"
#include "../../constants.h"
#include "../../comp/sprite.h"
#include "factories.h"
#include "../factories/weaponFactory.h"
#include "../../core/game.h"
#include "../../comp/spriteGroup.h"

void Game::equip(entt::registry& reg) {
    // make weapon means permament access to it

    makeDesertEagle(reg, this);
}

void Game::setupPlayer(entt::registry& reg)
{
    makePlayer(reg);

    auto view = reg.view<Player, Position>();

    for (auto e : view) {
        auto& p = view.get<Position>(e).pos;
                   
        auto sprite = scene->addPixmap(PLAYER_SPRITE_DEFAULT);
        p.setX(PLAYER_SPAWNPOS.x() - sprite->boundingRect().width() / 2);
        p.setY(PLAYER_SPAWNPOS.y() - sprite->boundingRect().height() / 2);
        sprite->setShapeMode(QGraphicsPixmapItem::HeuristicMaskShape);
        sprite->setZValue(PLAYER_Z_VALUE);
        sprite->setPos(PLAYER_SPAWNPOS.x(), PLAYER_SPAWNPOS.y());

        QGraphicsItemGroup* playerGroup = new QGraphicsItemGroup();
        scene->addItem(playerGroup);
        playerGroup->setPos(PLAYER_SPAWNPOS.x(), PLAYER_SPAWNPOS.y());
        playerGroup->addToGroup(sprite);

        reg.emplace<SpriteGroup>(e, playerGroup);
    }

    equip(reg);
}
