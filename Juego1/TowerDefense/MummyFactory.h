#pragma once
#include "EnemyFactory.h"
#include "Mummy.h"

class MummyFactory : public EnemyFactory
{
public:
	MummyFactory(Game* game);
	Enemy* createEnemy() override;
};

