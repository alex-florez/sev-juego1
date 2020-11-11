#pragma once


#include "Point.h"
#include "Enemy.h"

/// <summary>
/// Clase que representa un generador de enemigos 
/// situado en el mapa.
/// </summary>
class EnemyGenerator
{
public:
	EnemyGenerator(int pathId, int x, int y, Game* game);
	Enemy* createEnemy();


private:
	Game* game;
	int x;
	int y;
	int pathId; // Id de la trayectoria que deben seguir los enemigos generados.
	Point* startPoint; // Punto de inicio en el que aparecerán los enemigos.
};

