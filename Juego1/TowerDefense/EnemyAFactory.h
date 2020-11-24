#pragma once
#include "EnemyFactory.h"
class EnemyAFactory : public EnemyFactory
{
public:
	EnemyAFactory();
	Enemy* createEnemy() override;
};

