#include "ToolKit.h"

ToolKit::ToolKit(float x, float y, int aliveTicks, Game* game)
	: PowerUp("res/tool.png", 32, 32, aliveTicks, x, y, game)
{
	this->glowAnimation = new Animation("res/RedMist.png", 64, 64, 256, 64, 1, 4, true, game);
}

void ToolKit::effect(Tower* tower)
{
	tower->repair();
	tower->applyingPowerUp = true;
	this->used = true;
}

PowerUp* ToolKit::clone() {
	PowerUp* clone = new ToolKit(x, y, ticksAlive, game);
	clone->collected = this->collected;
	return clone;
}