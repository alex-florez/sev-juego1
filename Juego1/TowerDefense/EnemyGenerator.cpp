#include "EnemyGenerator.h"

EnemyGenerator::EnemyGenerator(Game* game) {
	this->game = game;
	// Inicializar factorías de enemigos
	this->factories['A'] = new EnemyAFactory(game);
	this->factories['B'] = new EnemyBFactory(game);
	this->factories['C'] = new EnemyCFactory(game);
	this->allGenerated = false;
}


Enemy* EnemyGenerator::createEnemy() {
	Enemy* e = nullptr;
	this->ticksUntilNextSpawn--;

	if (this->ticksUntilNextSpawn <= 0 &&
		this->actualHorde != nullptr && this->generatedEnemies < this->actualHorde->totalNumberOfEnemies) {
		// Id de path aleatorio
		int randomPathId = rand() % spawnPoints.size() + 1;
		Point* startingPoint = this->spawnPoints[randomPathId];
		e = this->factories[this->actualHorde->next()]->createEnemy();
		e->x = startingPoint->getX() * TILE_WIDTH + TILE_WIDTH / 2;
		e->y = startingPoint->getY() * TILE_HEIGHT + TILE_HEIGHT / 2;
		e->pathId = randomPathId;
		e->nextPoint = new Point(startingPoint->getX()-1, startingPoint->getY());
		this->ticksUntilNextSpawn = this->randomInt(this->actualHorde->spawnFrequencyRange[0], 
													this->actualHorde->spawnFrequencyRange[1]);
		this->generatedEnemies++;
		this->allGenerated = generatedEnemies == actualHorde->totalNumberOfEnemies;
	}

	
	return e;
}

void EnemyGenerator::setNextHorde(Horde* horde, int delay)
{
	this->actualHorde = horde;
	this->ticksUntilNextSpawn = delay + this->randomInt(horde->spawnFrequencyRange[0],
												horde->spawnFrequencyRange[1]);
	this->generatedEnemies = 0;
	this->allGenerated = false;
}

int EnemyGenerator::randomInt(int a, int b) {
	return rand() % (b - a + 1) + a;
}