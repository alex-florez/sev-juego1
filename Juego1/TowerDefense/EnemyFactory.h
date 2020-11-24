#pragma once

#include "Enemy.h"

class EnemyFactory
{
public:
	EnemyFactory(Game* game);
	virtual Enemy* createEnemy() = 0;

	Game* game;
};

