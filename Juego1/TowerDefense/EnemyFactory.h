#pragma once

#include "Enemy.h"

class EnemyFactory
{
public:
	EnemyFactory();
	virtual Enemy* createEnemy();
};

