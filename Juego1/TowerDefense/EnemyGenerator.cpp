#include "EnemyGenerator.h"

EnemyGenerator::EnemyGenerator(Game* game) {
	this->game = game;
}


Enemy* EnemyGenerator::createEnemy() {
	Enemy* e = nullptr;
	this->ticksUntilNextSpawn--;

	if (this->ticksUntilNextSpawn <= 0 && this->generatedEnemies < this->actualHorde->totalNumberOfEnemies) {
		// Id de path aleatorio
		int randomPathId = rand() % spawnPoints.size() + 1;
		Point* startingPoint = this->spawnPoints[randomPathId];
		e = new Enemy(startingPoint->getX() * TILE_WIDTH + TILE_WIDTH / 2, 
			startingPoint->getY() * TILE_HEIGHT + TILE_HEIGHT / 2, 2, this->game);
		e->pathId = randomPathId;
		e->nextPoint = new Point(startingPoint->getX()-1, startingPoint->getY());
		this->ticksUntilNextSpawn = this->randomInt(this->actualHorde->spawnFrequencyRange[0], 
													this->actualHorde->spawnFrequencyRange[1]);
		this->generatedEnemies++;
	}

	
	return e;
}

void EnemyGenerator::setNextHorde(Horde* horde)
{
	this->actualHorde = horde;
	this->ticksUntilNextSpawn = this->randomInt(horde->spawnFrequencyRange[0],
												horde->spawnFrequencyRange[1]);
	this->generatedEnemies = 0;
}

int EnemyGenerator::randomInt(int a, int b) {
	return rand() % (b - a + 1) + a;
}