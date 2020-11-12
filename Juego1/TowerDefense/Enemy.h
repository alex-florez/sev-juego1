#pragma once

#include "Actor.h"
#include "Animation.h"
#include "Point.h"
#include "Path.h"
#include "Tower.h"

#define ENEMY_SPEED 2

class Enemy : public Actor
{
public:
	Enemy(float x, float y, float speed, Game* game);
	void update();
	void draw() override;
	void impacted(); // Enemigo recibe un impacto
	void attack(Tower* tower); // El enemigo ataca a una torre.

	Animation* aMoving;
	Animation* aDying;
	Animation* animation; // Referencia a la animaci�n actual.

	int attackFrequency; // Frecuencia de ataque del enemigo
	int ticksUntilNextAttack; // Ticks hasta efectuar el siguiente ataque.
};

