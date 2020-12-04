#include "PowerUpGenerator.h"

PowerUpGenerator::PowerUpGenerator(Game* game)
{
	this->game = game;
	this->ticksUntilNextPowerUp = randomInt(POWER_UP_MIN_SPAWN_FREQ, POWER_UP_MAX_SPAWN_FREQ);
	this->types[0] = 'M'; // MedKit
	this->types[1] = 'T'; // Toolkit
}

PowerUp* PowerUpGenerator::createPowerUp() {
	this->ticksUntilNextPowerUp--;
	PowerUp* pwu = nullptr;

	if (this->ticksUntilNextPowerUp <= 0) {
		int rX = rand() % (WIDTH - 50 - 50) + 50;
		int rY = rand() % (HEIGHT - 50 - 50) + 50;
		int randomAliveTicks = randomInt(POWER_UP_MIN_ALIVE_TICKS, POWER_UP_MAX_ALIVE_TICKS);
		switch (randomType())
		{
		case 'M':
			pwu = new MedKit(rX, rY, randomAliveTicks, game);
			break;
		case 'T':
			pwu = new ToolKit(rX, rY, randomAliveTicks, game);
			break;
		}

		this->ticksUntilNextPowerUp = randomInt(POWER_UP_MIN_SPAWN_FREQ, POWER_UP_MAX_SPAWN_FREQ);
	}
	
	return pwu;
}

PowerUp* PowerUpGenerator::createRandomPowerUpAt(float x, float y)
{
	PowerUp* pwu = nullptr;
	double rDouble = (double)rand() / RAND_MAX;

	if (rDouble < 0.2) { // Distribución aleatoria: 20 % de probabilidades de que se genere un powerUp
		int randomAliveTicks = randomInt(POWER_UP_MIN_ALIVE_TICKS, POWER_UP_MAX_ALIVE_TICKS);
		switch (randomType())
		{
		case 'M':
			pwu = new MedKit(x, y, randomAliveTicks, game);
			break;
		case 'T':
			pwu = new ToolKit(x, y, randomAliveTicks, game);
			break;
		}
	}

	return pwu;
}

int PowerUpGenerator::randomInt(int a, int b)
{
	return rand() % (b - a + 1) + a;
}

char PowerUpGenerator::randomType() {
	double rDouble = (double)rand() / RAND_MAX;
	int pos = 0;

	if (rDouble < TOOLKIT_PROB)
		pos = 1; // Toolkit
	else
		pos = 0; // MedKit
	return this->types[pos];
}
