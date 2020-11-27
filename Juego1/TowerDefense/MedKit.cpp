#include "MedKit.h"

MedKit::MedKit(float x, float y, int aliveTicks, Game* game)
	: PowerUp("res/medkit.png", 32, 32, aliveTicks, x, y, game)
{
}


void MedKit::effect(Tower* tower)
{
	tower->health += 50;
	this->used = true; // Establecer el powerUp como ya utilizado.
}

PowerUp* MedKit::clone()
{
	return new MedKit(x, y, ticksAlive, game);
}
