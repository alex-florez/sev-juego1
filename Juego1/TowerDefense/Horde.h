#pragma once


/// <summary>
/// Clase que representa una horda de enemigos
/// dentro del juego.
/// </summary>
class Horde
{
public:
	Horde(int totalEnemies, int minSpawnFreq, int maxSpawnFreq);

	int totalNumberOfEnemies; // n� total de enemigos
	int spawnFrequencyRange[2]; // Rango de frecuencias de aparici�n
};

