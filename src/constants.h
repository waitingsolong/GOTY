#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <qpoint.h>
#include <qvector2d.h>

// const 

constexpr QVector2D NULL_VECTOR(0.0f, 0.0f);

// game settings 

constexpr float SCREEN_WIDTH = 1024;
constexpr float SCREEN_HEIGHT = 768;

constexpr int FPS = 50; 
constexpr int MS_PER_FRAME = 1000 / FPS;

constexpr int PLAYER_Z_VALUE = 1;

// initialization 

const QVector2D PLAYER_SPAWNPOS{ SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT * 2.0 / 3.0f };
constexpr __int8 PLAYER_AMOUNT_OF_LIFES{ 3 };
constexpr float PLAYER_BASIC_ACCELERATION_M = 1.0f;

// texture paths

const QString PLAYER_SPRITE_DEFAULT = ":player/fly_fly.png";

const QString WEAPON_SPRITE_DEAGLE = ":weapon/deagle.png";

// physics 

constexpr float REPULSION_COEFF = 3.0f; 
constexpr float ACCELERATION_LOSS_COEFF = 0.5f; 
constexpr float VELOCITY_LOSS_COEFF = 0.5f;

// weapon stats 
// (shot interval measures in ms) 

enum WeaponLabels {
    WEAPON_LABEL_DEAGLE
};

constexpr float WEAPON_SHOT_VELOCITY_DEAGLE = 10.0f;
constexpr int WEAPON_SHOT_INTERVAL_DEAGLE = 500;
constexpr int WEAPON_DAMAGE_DEAGLE = 100;

#endif //CONSTANTS_H