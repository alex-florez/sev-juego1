#pragma once
#include "EnemyFactory.h"
#include "EnemyA.h"

class EnemyAFactory : public EnemyFactory
{
public:
	EnemyAFactory(Game* game);
	Enemy* createEnemy() override;
};

