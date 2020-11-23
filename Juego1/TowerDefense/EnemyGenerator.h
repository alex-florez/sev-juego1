#pragma once

#include <map>

#include "Point.h"
#include "Enemy.h"
#include "Horde.h"

/// <summary>
/// Clase que representa un generador de enemigos que crea
/// enemigos en distintos puntos del mapa que siguen distintas trayectorias
/// y que varían en número según la Horda indicada.
/// </summary>
class EnemyGenerator
{
public:
	EnemyGenerator(Game* game);
	Enemy* createEnemy();
	void setNextHorde(Horde* horde);

	// Puntos de Spawn (int: id del camino, Point: punto de spawn)
	map<int, Point*> spawnPoints;

private:
	Game* game;

	// Generación aleatoria de enemigos
	Horde* actualHorde; // Referencia a la horda actual
	int ticksUntilNextSpawn; // Vble de control 
	int generatedEnemies; // Almacena el nº de enemigos generados hasta el momento.

	
	

private:
	/// <summary>
	/// Genera un entero aleatorio dentro del rango pasado
	/// como parámetro para crear cierta varianza en la generación
	/// de enemigos.
	/// </summary>
	/// <returns></returns>
	int randomInt(int a, int b);

};

