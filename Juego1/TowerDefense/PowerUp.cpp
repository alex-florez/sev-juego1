#include "PowerUp.h"

PowerUp::PowerUp(string filename, float width, float height, int ticksAlive, float x, float y, Game* game)
	: Actor(filename, x, y, width, height, game)
{
	this->collected = false;
	this->used = false;
	this->ticksAlive = ticksAlive;
}

void PowerUp::update()
{
	this->ticksAlive--;
}
