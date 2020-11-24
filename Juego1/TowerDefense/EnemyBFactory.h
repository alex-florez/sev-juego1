#pragma once
#include "EnemyFactory.h"
#include "EnemyB.h"

class EnemyBFactory : public EnemyFactory
{
public:
	EnemyBFactory(Game* game);
	Enemy* createEnemy() override;
};

