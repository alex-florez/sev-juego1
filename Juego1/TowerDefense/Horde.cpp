#include "Horde.h"


Horde::Horde(int totalEnemies, int minSpawnFreq, int maxSpawnFreq) {
	this->totalNumberOfEnemies = totalEnemies;
	this->spawnFrequencyRange[0] = minSpawnFreq;
	this->spawnFrequencyRange[1] = maxSpawnFreq;
}

