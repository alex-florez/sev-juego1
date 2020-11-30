#include "ExecutionerFactory.h"

ExecutionerFactory::ExecutionerFactory(Game* game)
	: EnemyFactory(game)
{
}

Enemy* ExecutionerFactory::createEnemy()
{
	return new Executioner(0, 0, 2.4, game);
}
