#pragma once
#include "EnemyFactory.h"
#include "Executioner.h"

class ExecutionerFactory : public EnemyFactory
{
public:
	ExecutionerFactory(Game* game);
	Enemy* createEnemy() override;
};

