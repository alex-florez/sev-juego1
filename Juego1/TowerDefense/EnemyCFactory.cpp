#include "EnemyCFactory.h"

EnemyCFactory::EnemyCFactory(Game* game)
	: EnemyFactory(game)
{
}

Enemy* EnemyCFactory::createEnemy()
{
	return new EnemyC(0, 0, 2, game);
}
