#pragma once

#include "Actor.h"
#include "Projectile.h"
#include "Audio.h"
#include "Animation.h"

#define PLAYER_SPEED 3
#define PLAYER_INITIAL_RESOURCES 500
#define PLAYER_HIT_RESOURCES 25 // Recursos añadidos al jugador cuando un enemigo es impactado.
#define PLAYER_KILL_RESOURCES 50 // Recursos añadidos al jugador cuando elimina a un enemigo.

class Player : public Actor
{
public:
	Player(float x, float y, Game* game);

	void update();
	void moveX(float axis);
	void moveY(float axis);
	void draw() override;
	void jump(); // Saltar
	void loseLife();
	bool isOver(Actor* actor);

	bool onAir; // indica si el jugador está en el aire.

	int shootCadence = 30;
	int shootTime = 0;

	// Audio
	Audio* audioShoot;
	Audio* audioJumpOverEnemy;

	// Animaciones
	Animation* aIdleRight;
	Animation* aIdleLeft;
	Animation* aRunningRight;
	Animation* aRunningLeft;

	Animation* aShootingLeft;
	Animation* aShootingRight;

	// Salto
	Animation* aJumpingRight;
	Animation* aJumpingLeft;

	Animation* animation;

	// Estado y orientación
	int state;
	int orientation;

	// Vidas y tiempo de invulnerabilidad
	int lifes = 3;
	int invulnerableTime = 0;

	// Recursos/materiales disponibles
	int availableResources;

	// Enemigos eliminados en la ronda actual
	int killedEnemiesInActualHorde = 0;
};


