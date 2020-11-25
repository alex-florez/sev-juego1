#pragma once

#include "Gem.h"
#include "BlueGem.h"
#include "YellowGem.h"
#include "MagentaGem.h"


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
	int spawnFreqRange[2]; // Rango de frecuencia de creación

	int getRandomInt();
	float getRandomX();
	float getRandomY();
};

