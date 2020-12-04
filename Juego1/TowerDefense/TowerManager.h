#pragma once

#include "Tower.h"
#include "SoundEffect.h"

#include <map>

/// <summary>
/// Manager de los objetos Tower
/// </summary>
class TowerManager
{
public:
	TowerManager(Game* game);
	void draw();
	Tower* getTower(float x, float y);
	void add(int key, Tower* tower);
	void remove(int key);
	bool allDestroyed();

	Game* game;
	map<int, Tower*> towers;
	
	// Sonido de explosión de una torre compartido por todas las torres
	SoundEffect* explosionSound;
};

