#include "EnemyBFactory.h"

EnemyBFactory::EnemyBFactory(Game* game)
	: EnemyFactory(game)
{
}

Enemy* EnemyBFactory::createEnemy()
{
	return new EnemyB(0, 0, 2, game);
}
