#include "PowerUpGenerator.h"

PowerUpGenerator::PowerUpGenerator(Game* game)
{
	this->game = game;
	this->ticksUntilNextPowerUp = randomInt(POWER_UP_MIN_SPAWN_FREQ, POWER_UP_MAX_SPAWN_FREQ);
}

PowerUp* PowerUpGenerator::createPowerUp() {
	this->ticksUntilNextPowerUp--;
	PowerUp* pwu = nullptr;

	if (this->ticksUntilNextPowerUp <= 0) {
		int rX = rand() % (WIDTH - 50 - 50) + 50;
		int rY = rand() % (HEIGHT - 50 - 50) + 50;
		int randomAliveTicks = randomInt(POWER_UP_MIN_ALIVE_TICKS, POWER_UP_MAX_ALIVE_TICKS);
		pwu = new MedKit(rX, rY, randomAliveTicks, game);
		this->ticksUntilNextPowerUp = randomInt(POWER_UP_MIN_SPAWN_FREQ, POWER_UP_MAX_SPAWN_FREQ);
	}
	
	return pwu;
}

int PowerUpGenerator::randomInt(int a, int b)
{
	return rand() % (b - a + 1) + a;
}
