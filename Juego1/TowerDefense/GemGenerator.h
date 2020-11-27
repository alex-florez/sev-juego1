#pragma once

#include "Gem.h"
#include "BlueGem.h"
#include "YellowGem.h"
#include "MagentaGem.h"


#define GEM_MIN_SPAWN_FREQ 200
#define GEM_MAX_SPAWN_FREQ 350

#define GEM_MIN_ALIVE_TICKS 90
#define GEM_MAX_ALIVE_TICKS 120


/// <summary>
/// Clase que representa un generador de diferentes
/// gemas collecionables.
/// </summary>
class GemGenerator
{
public:
	GemGenerator(Game* game);
	Gem* createGem();
	

private:
	Game* game;
	char types[3]; // Tipos de gemas
	int ticksUntilNextGem;
	int spawnFreqRange[2]; // Rango de frecuencia de creaci�n

	int getRandomInt(int a, int b);
	float getRandomX();
	float getRandomY();
};

