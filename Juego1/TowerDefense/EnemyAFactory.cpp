#include "EnemyAFactory.h"

EnemyAFactory::EnemyAFactory(Game* game)
	: EnemyFactory(game)
{
}

Enemy* EnemyAFactory::createEnemy()
{
	return new EnemyA(0, 0, 1.4, game);
}
