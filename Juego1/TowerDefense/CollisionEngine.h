#pragma once

#include <map>
#include <list>

#include "Tower.h"
#include "Enemy.h"

/// <summary>
/// Clase que modela un motor muy simple de colisiones.
/// </summary>
class CollisionEngine
{
public:
	CollisionEngine();
	void update();


	map<int, Tower*> towers;
	list<Enemy*> enemies;

};

