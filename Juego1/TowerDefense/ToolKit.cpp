#include "ToolKit.h"

ToolKit::ToolKit(float x, float y, int aliveTicks, Game* game)
	: PowerUp("res/tool.png", 32, 32, aliveTicks, x, y, game)
{
	this->glowAnimation = new Animation("res/RedMist.png", 64, 64, 256, 64, 1, 4, true, game);
	this->pickUpSound = new SoundEffect("res/sounds/metal_hit.wav");
	this->applySound = new SoundEffect("res/sounds/repair.wav");
}

void ToolKit::effect(Tower* tower)
{
	if (tower->state == Tower::TowerState::DESTROYED) {
		tower->repair();
		tower->applyingPowerUp = true;
		this->used = true;
		this->applySound->play(); // Reproducir sonido
	}
}

PowerUp* ToolKit::clone() {
	PowerUp* clone = new ToolKit(x, y, ticksAlive, game);
	clone->collected = this->collected;
	return clone;
}