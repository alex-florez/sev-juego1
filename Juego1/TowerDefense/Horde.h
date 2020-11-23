#pragma once


/// <summary>
/// Clase que representa una horda de enemigos
/// dentro del juego.
/// </summary>
class Horde
{
public:
	Horde(int totalEnemies, int minSpawnFreq, int maxSpawnFreq);

	int totalNumberOfEnemies; // nº total de enemigos
	int spawnFrequencyRange[2]; // Rango de frecuencias de aparición
};

