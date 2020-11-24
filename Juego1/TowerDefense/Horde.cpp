#include "Horde.h"


Horde::Horde(int totalEnemies, int minSpawnFreq, int maxSpawnFreq) {
	this->totalNumberOfEnemies = totalEnemies;
	this->spawnFrequencyRange[0] = minSpawnFreq;
	this->spawnFrequencyRange[1] = maxSpawnFreq;
}

Horde::Horde(int id, queue<char> enemies, int totalEnemies, int minSpawnFreq, int maxSpawnFreq)
{
	this->id = id;
	this->enemies = enemies;
	this->totalNumberOfEnemies = totalEnemies;
	this->spawnFrequencyRange[0] = minSpawnFreq;
	this->spawnFrequencyRange[1] = maxSpawnFreq;
}

char Horde::next() {
	char next = enemies.front();
	enemies.pop();
	return next;
}
