#pragma once
#include "EnemyFactory.h"
#include "EnemyC.h"

class EnemyCFactory : public EnemyFactory
{
public:
	EnemyCFactory(Game* game);
	Enemy* createEnemy() override;
};

