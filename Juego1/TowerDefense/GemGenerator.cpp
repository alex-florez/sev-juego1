#include "GemGenerator.h"

GemGenerator::GemGenerator(Game* game)
{
    this->game = game;
    this->spawnFreqRange[0] = GEM_MIN_SPAWN_FREQ;
    this->spawnFreqRange[1] = GEM_MAX_SPAWN_FREQ;
    this->ticksUntilNextGem = getRandomInt(this->spawnFreqRange[0], this->spawnFreqRange[1]);
    this->types[0] = 'B';
    this->types[1] = 'Y';
    this->types[2] = 'M';

}

Gem* GemGenerator::createGem()
{
	this->ticksUntilNextGem--;
	Gem* newGem = nullptr;
	if(this->ticksUntilNextGem <= 0) {
		newGem = createRandomGem();
		if (newGem != nullptr) {
			newGem->x = getRandomX();
			newGem->y = getRandomY();
			this->ticksUntilNextGem = getRandomInt(this->spawnFreqRange[0], this->spawnFreqRange[1]);
		}
	}

	return newGem;
}


Gem* GemGenerator::createRandomGemAt(float x, float y)
{
	Gem* gem = nullptr;
	
	double rDouble = (double)rand() / RAND_MAX;

	if (rDouble < 0.35) { // Distribución aleatoria: 35 % de probabilidades de que se genere una gema
		gem = createRandomGem();
		gem->x = x;
		gem->y = y;
	}

	return gem;
}

int GemGenerator::getRandomInt(int a, int b)
{
    return rand() % (b - a + 1) + a;
}

Gem* GemGenerator::createRandomGem()
{
	Gem* newGem = nullptr;
	int randomPos = rand() % 3;
	int randomAliveTicks = getRandomInt(GEM_MIN_ALIVE_TICKS, GEM_MAX_ALIVE_TICKS);
	switch (this->types[randomPos])
	{
	case 'B':
		newGem = new BlueGem(0, 0, randomAliveTicks, game);
		break;
	case 'Y':
		newGem = new YellowGem(0, 0, randomAliveTicks, game);
		break;
	case 'M':
		newGem = new MagentaGem(0, 0, randomAliveTicks, game);
		break;
	default:
		return nullptr;
	}
	return newGem;
}

float GemGenerator::getRandomX()
{
	int minX = 100;
	int maxX = WIDTH - 60;
	return (rand() % (maxX - minX + 1)) + minX;
}

float GemGenerator::getRandomY() {
	int minY = 50;
	int maxY = HEIGHT - 50;
	return rand() % (maxY - minY + 1) + minY;
}

