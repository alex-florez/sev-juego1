#include "MedKit.h"

MedKit::MedKit(float x, float y, int aliveTicks, Game* game)
	: PowerUp("res/medkit.png", 32, 32, aliveTicks, x, y, game)
{
	this->glowAnimation = new Animation("res/purpleGlow.png", 64, 64, 1920, 64, 1, 30, true, game);
	this->pickUpSound = new SoundEffect("res/sounds/itemPick2.wav");
	this->applySound = new SoundEffect("res/sounds/healing.wav");
}


void MedKit::effect(Tower* tower)
{
	if (tower->state == Tower::TowerState::ALIVE) {
		tower->health += 50;
		tower->applyingPowerUp = true;
		tower->isHealing = true; // Establecer que la torre se está curando.
		this->used = true; // Establecer el powerUp como ya utilizado.
		this->applySound->play(); // Reproducir sonido
	}
	
}

PowerUp* MedKit::clone()
{
	MedKit* clone = new MedKit(x, y, ticksAlive, game);
	clone->collected = this->collected;
	return clone;
}
