#pragma once

#include "Actor.h"
#include <math.h>


class Projectile : public Actor
{
public:
	Projectile(float x, float y, Game* game);
	void update();
	void moveTo(float x, float y);


	int speed; // Velocidad del proyectil
	int damage; // Daño causado por este proyectil
	bool impacted; // Indica si este proyectil ha impactado ya o no
};

