#pragma once
#include "EnemyFactory.h"
#include "Orc.h"

class OrcFactory : public EnemyFactory
{
public:
	OrcFactory(Game* game);
	Enemy* createEnemy() override;
};

