#include "MummyFactory.h"

MummyFactory::MummyFactory(Game* game)
	: EnemyFactory(game)
{
}

Enemy* MummyFactory::createEnemy()
{
	return new Mummy(0, 0, 1.4, game);
}
