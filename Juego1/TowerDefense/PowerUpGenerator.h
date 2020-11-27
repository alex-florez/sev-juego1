#pragma once

#include "Game.h"
#include "PowerUp.h"
#include "MedKit.h"
#include "ToolKit.h"

#define POWER_UP_MIN_SPAWN_FREQ 100
#define POWER_UP_MAX_SPAWN_FREQ 300

#define POWER_UP_MIN_ALIVE_TICKS 120
#define POWER_UP_MAX_ALIVE_TICKS 150

/// <summary>
/// Generador de powerups
/// </summary>
class PowerUpGenerator
{
public:
	PowerUpGenerator(Game* game);
	PowerUp* createPowerUp();

	int ticksUntilNextPowerUp;
	Game* game;
	char types[2]; // Array con los distintos tipos de powerUPs

private:
	int randomInt(int a, int b);
	char randomType();
};

