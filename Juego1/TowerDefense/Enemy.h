#pragma once

#include "Actor.h"
#include "Animation.h"
#include "Point.h"
#include "Path.h"
#include "Tower.h"
#include "Projectile.h"
#include "Pawn.h"

#define ENEMY_SPEED 2

class Enemy : public Pawn
{
public:
	Enemy(float x, float y, float speed, Game* game);
	void update();
	void draw() override;
	void impactedBy(Projectile* projectile); // Enemigo recibe un impacto
	void attack(Tower* tower); // El enemigo ataca a una torre.

	Animation* aMoving;
	Animation* aDying;
	Animation* animation; // Referencia a la animación actual.

	int attackFrequency; // Frecuencia de ataque del enemigo
	int ticksUntilNextAttack; // Ticks hasta efectuar el siguiente ataque.
	bool isCollisioning; // Flag que indica si el enemigo está colisionando con otro actor.
	int health; // Variable que almacena la salud de este enemigo.
};

