#include "UIPowerUp.h"

UIPowerUp::UIPowerUp(float x, float y, Game* game)
	: Actor("res/slot.png", x, y, 50, 50, game)
{
	this->powerUp = nullptr;

	this->clickSound = new SoundEffect("res/sounds/uiPickPowerup.wav");
}

void UIPowerUp::draw()
{
	Actor::draw();
	if (this->powerUp != nullptr)
		this->powerUp->draw();
}

bool UIPowerUp::empty()
{
	return this->powerUp == nullptr;
}

void UIPowerUp::clear()
{
	this->powerUp = nullptr;
}

void UIPowerUp::setPowerUp(PowerUp* powerUp)
{
	this->powerUp = powerUp;
	this->powerUp->x = x;
	this->powerUp->y = y;
}

