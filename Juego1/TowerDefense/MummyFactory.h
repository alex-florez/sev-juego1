#pragma once
#include "EnemyFactory.h"
#include "Mummy.h"

#define MUMMY_SPEED 1.7

class MummyFactory : public EnemyFactory
{
public:
	MummyFactory(Game* game);
	Enemy* createEnemy() override;
};

