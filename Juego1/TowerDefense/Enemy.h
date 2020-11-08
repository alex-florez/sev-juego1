#pragma once

#include "Actor.h"
#include "Animation.h"
#include "Point.h"
#include "Path.h"

#define ENEMY_SPEED 2

class Enemy : public Actor
{
public:
	Enemy(float x, float y, Game* game);
	void update();
	void draw() override;
	void impacted(); // Enemigo recibe un impacto

	Animation* aMoving;
	Animation* aDying;
	Animation* animation; // Referencia a la animación actual.

	Point* nextPoint;
	Point* lastPoint;
	Path* path;

	int state;
	float vxIntelligence;

private:
	Point* getPointPos(); // Devuelve la posición del enemigo en la matriz del mapa.
};

