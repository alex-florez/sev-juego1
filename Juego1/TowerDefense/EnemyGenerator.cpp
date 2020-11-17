#include "EnemyGenerator.h"

EnemyGenerator::EnemyGenerator(int pathId, int x, int y, int spawnFrequency, int numberOfEnemies, Game* game) {
	this->x = x;
	this->y = y;
	this->game = game;
	this->pathId = pathId;
	this->startPoint = new Point(x-1, y);
	this->spawnFrequency = spawnFrequency;
	this->ticksUntilNextSpawn = spawnFrequency + this->randomInt(-20, 20);
	this->numberOfEnemies = numberOfEnemies;
	this->generatedEnemies = 0;
}


Enemy* EnemyGenerator::createEnemy() {
	Enemy* e = nullptr;
	this->ticksUntilNextSpawn--;

	if (this->ticksUntilNextSpawn <= 0 && this->generatedEnemies < this->numberOfEnemies) {
		e = new Enemy(this->x * TILE_WIDTH + TILE_WIDTH / 2, this->y * TILE_HEIGHT + TILE_HEIGHT / 2, 2, this->game);
		e->pathId = this->pathId;
		e->nextPoint = this->startPoint;
		this->ticksUntilNextSpawn = this->spawnFrequency + this->randomInt(-20, 20);
		this->generatedEnemies++;
	}

	
	return e;
}

int EnemyGenerator::randomInt(int a, int b) {
	return rand() % (b - a + 1) + a;
}