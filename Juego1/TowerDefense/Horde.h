#pragma once

#include <queue>

using namespace std;

/// <summary>
/// Clase que representa una horda de enemigos
/// dentro del juego.
/// </summary>
class Horde
{
public:
	Horde(int totalEnemies, int minSpawnFreq, int maxSpawnFreq);
	Horde(int id, queue<char> enemies, int totalEnemies, int minSpawnFreq, int maxSpawnFreq);
	char next();

	queue<char> enemies; // Cola FIFO de caracteres que representan los distintos tipos de enemigos de esta horda.
	int id; // Id de la horda
	int totalNumberOfEnemies; // nº total de enemigos
	int spawnFrequencyRange[2]; // Rango de frecuencias de aparición
};

