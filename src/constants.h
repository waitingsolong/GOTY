#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <qpoint.h>
#include <qvector2d.h>

// game settings 

constexpr float SCREEN_WIDTH = 1024;
constexpr float SCREEN_HEIGHT = 768;

constexpr int FPS = 30; 
constexpr int MS_PER_FRAME = 1000 / FPS;

// initialization 

constexpr QVector2D PLAYER_SPAWNPOS{ SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT * 2.0f / 3.0f };
constexpr __int8 PLAYER_AMOUNT_OF_LIFES{ 3 };

// texture paths

const QString PLAYER_SPRITE_DEFAULT = ":fly_fly.png";

// physics 

constexpr float PLAYER_BASE_ACCELERATION = 3.0f; 

constexpr float REPULSION_COEFF = 3.0f; 
constexpr float ACCELERATION_LOSS = 0.5f; 

#endif //CONSTANTS_H