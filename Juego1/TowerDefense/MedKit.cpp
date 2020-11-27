#include "MedKit.h"

MedKit::MedKit(float x, float y, int aliveTicks, Game* game)
	: PowerUp("res/medkit.png", 32, 32, aliveTicks, x, y, game)
{
	this->glowAnimation = new Animation("res/purpleGlow.png", 64, 64, 1920, 64, 1, 30, true, game);
}


void MedKit::effect(Tower* tower)
{
	tower->health += 50;
	tower->applyingPowerUp = true;
	this->used = true; // Establecer el powerUp como ya utilizado.
}

PowerUp* MedKit::clone()
{
	MedKit* clone = new MedKit(x, y, ticksAlive, game);
	clone->collected = this->collected;
	return clone;
}
