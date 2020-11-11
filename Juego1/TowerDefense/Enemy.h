#pragma once

#include "Actor.h"
#include "Animation.h"
#include "Point.h"
#include "Path.h"

#define ENEMY_SPEED 2

class Enemy : public Actor
{
public:
	Enemy(float x, float y, float speed, Game* game);
	void update();
	void draw() override;
	void impacted(); // Enemigo recibe un impacto

	Animation* aMoving;
	Animation* aDying;
	Animation* animation; // Referencia a la animación actual.

	int state;
};

