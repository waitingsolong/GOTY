#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <qpoint.h>
#include <qvector2d.h>

// const 

inline constexpr QVector2D NULL_VECTOR(0.0f, 0.0f);

// game settings 

inline constexpr float SCREEN_WIDTH = 1024;
inline constexpr float SCREEN_HEIGHT = 768;

inline constexpr int FPS = 50; 
inline constexpr int MS_PER_FRAME = 1000 / FPS;

inline constexpr int PLAYER_Z_VALUE = 1;

// initialization 

inline const QVector2D PLAYER_SPAWNPOS{ SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT * 2.0 / 3.0f };
inline constexpr __int8 PLAYER_AMOUNT_OF_LIFES{ 3 };
inline constexpr float PLAYER_BASIC_ACCELERATION_M = 1.0f;

// texture paths

inline const QString PLAYER_SPRITE_DEFAULT = ":player/fly_fly.png";

inline const QString WEAPON_SPRITE_DEAGLE = ":weapon/deagle.png";

inline const QString BULLET_SPRITE_50AE = ":bullet/50AE.png";

// physics 

inline constexpr float REPULSION_COEFF = 3.0f; 
inline constexpr float ACCELERATION_LOSS_COEFF = 0.5f; 
inline constexpr float VELOCITY_LOSS_COEFF = 0.5f;

// weapon stats 
// (shot interval measures in ms) 

// (corresponding to key on keyboard)
extern enum WeaponLabels {
    WEAPON_LABEL_DEAGLE = 1
};

inline constexpr float WEAPON_SHOT_VELOCITY_DEAGLE = 10.0f;
inline constexpr int WEAPON_SHOT_INTERVAL_DEAGLE = 500;
inline constexpr int WEAPON_DAMAGE_DEAGLE = 100;

#endif //CONSTANTS_H