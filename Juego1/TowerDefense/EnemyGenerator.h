#pragma once

#include <map>

#include "Point.h"
#include "Enemy.h"
#include "Horde.h"
#include "EnemyFactory.h"
#include "EnemyAFactory.h"
#include "EnemyBFactory.h"
#include "EnemyCFactory.h"

/// <summary>
/// Clase que representa un generador de enemigos que crea
/// enemigos en distintos puntos del mapa que siguen distintas trayectorias
/// y que var�an en n�mero seg�n la Horda indicada.
/// </summary>
class EnemyGenerator
{
public:
	EnemyGenerator(Game* game);
	Enemy* createEnemy();

	/// <summary>
	/// Establece la siguiente horda pasada como par�metro y
	/// a�ade un delay en los ticksUntilNextSpawn para esperar
	/// al comienzo de la horda.
	/// </summary>
	/// <param name="horde"></param>
	/// <param name="delay"></param>
	void setNextHorde(Horde* horde, int delay);

	// Puntos de Spawn (int: id del camino, Point: punto de spawn)
	map<int, Point*> spawnPoints;
	// Factor�as para construir los distintos tipos de enemigos.
	map<char, EnemyFactory*> factories;
	bool allGenerated; // Toma el valor true cuando todos los enemigos han sido generados
	
private:
	Game* game;

	// Generaci�n aleatoria de enemigos
	Horde* actualHorde; // Referencia a la horda actual
	int ticksUntilNextSpawn; // Vble de control 
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

