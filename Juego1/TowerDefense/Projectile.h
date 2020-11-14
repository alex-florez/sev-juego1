#pragma once

#include "Actor.h"
#include <math.h>

class Projectile : public Actor
{
public:
	Projectile(float x, float y, Game* game);
	void update();
	void moveTo(float x, float y);


	int speed;
};

