#pragma once

#include "UIPowerUp.h"

#include <list>

/// <summary>
/// Clase que representa el inventario de powerUps
/// para las torres.
/// </summary>
class PowerUpInventory
{
public:
	PowerUpInventory(Game* game);
	void draw();
	UIPowerUp* getSlot(float x, float y);
	void addPowerUp(PowerUp* powerUp);
	bool isFull();

	list<UIPowerUp*> slots;
};

