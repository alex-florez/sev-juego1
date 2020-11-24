#pragma once
#include "EnemyFactory.h"
class EnemyBFactory : public EnemyFactory
{
public:
	EnemyBFactory();
	Enemy* createEnemy() override;
};

