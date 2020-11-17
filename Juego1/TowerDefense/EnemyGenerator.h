#pragma once


#include "Point.h"
#include "Enemy.h"

/// <summary>
/// Clase que representa un generador de enemigos 
/// situado en un lugar del mapa.
/// </summary>
class EnemyGenerator
{
public:
	EnemyGenerator(int pathId, int x, int y, int spawnFrequency, int numberOfEnemies, Game* game);
	Enemy* createEnemy();


private:
	Game* game;
	int x;
	int y;
	int pathId; // Id de la trayectoria que deben seguir los enemigos generados.
	Point* startPoint; // Punto de inicio en el que aparecer�n los enemigos.

	// Generaci�n aleatoria de enemigos
	int spawnFrequency; // Frecuencia de aparici�n
	int ticksUntilNextSpawn; // Vble de control 
	int numberOfEnemies; // N� de enemigos que se van a generar
	int generatedEnemies; // Almacena el n� de enemigos generados hasta el momento.
	

private:
	/// <summary>
	/// Genera un entero aleatorio dentro del rango pasado
	/// como par�metro para crear cierta varianza en la generaci�n
	/// de enemigos.
	/// </summary>
	/// <returns></returns>
	int randomInt(int a, int b);
};

