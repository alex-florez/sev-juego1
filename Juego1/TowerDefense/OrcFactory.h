#pragma once
#include "EnemyFactory.h"
#include "Orc.h"

#define ORC_SPEED 1.32

class OrcFactory : public EnemyFactory
{
public:
	OrcFactory(Game* game);
	Enemy* createEnemy() override;
};

