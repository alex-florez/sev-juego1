#pragma once
#include "EnemyFactory.h"
#include "Executioner.h"

#define EXECUTIONER_SPEED 2.3

class ExecutionerFactory : public EnemyFactory
{
public:
	ExecutionerFactory(Game* game);
	Enemy* createEnemy() override;
};

