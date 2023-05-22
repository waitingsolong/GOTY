#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <qpoint.h>
#include <qvector2d.h>

constexpr int SCREEN_WIDTH = 1024;
constexpr int SCREEN_HEIGHT = 768;

constexpr int FPS = 30; 
constexpr int MS_PER_FRAME = 1000 / FPS;

constexpr int SDL_DEFAULT_REPEAT_DELAY;
constexpr int SDL_DEFAULT_REPEAT_INTERVAL;

// initialization 

constexpr QPointF PLAYER_SPAWNPOINT{ SCREEN_WIDTH / 2, SCREEN_HEIGHT * 2 / 3 };
constexpr __int8 PLAYER_AMOUNT_OF_LIFES{ 3 };

// texture paths

//const QString PLAYER_SPRITE_DEFAULT = ":fly_fly.png";

#endif //CONSTANTS_H