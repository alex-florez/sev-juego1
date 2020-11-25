#include "GemGenerator.h"




GemGenerator::GemGenerator(Game* game)
{
    this->game = game;
    this->spawnFreqRange[0] = 150;
    this->spawnFreqRange[1] = 300;
    this->ticksUntilNextGem = getRandomInt();
    this->types[0] = 'B';
    this->types[1] = 'Y';
    this->types[2] = 'M';

}

Gem* GemGenerator::createGem()
{
	this->ticksUntilNextGem--;
	Gem* newGem = nullptr;
	if(this->ticksUntilNextGem <= 0) {
		int randomPos = rand() % 3;
		switch (this->types[randomPos])
		{
		case 'B':
			newGem = new BlueGem(0, 0, game);
			break;
		case 'Y':
			newGem = new YellowGem(0, 0, game);
			break;
		case 'M':
			newGem = new MagentaGem(0, 0, game);
			break;
		default:
			return nullptr;
		}
		newGem->x = getRandomX();
		newGem->y = getRandomY();
		this->ticksUntilNextGem = getRandomInt();
	}

	return newGem;
}


int GemGenerator::getRandomInt()
{
    int a = this->spawnFreqRange[0];
    int b = this->spawnFreqRange[1];
    return rand() % (b - a + 1) + a;
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

