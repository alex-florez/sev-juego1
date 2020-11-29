#include "OrcFactory.h"

OrcFactory::OrcFactory(Game* game)
	: EnemyFactory(game)
{
}

Enemy* OrcFactory::createEnemy()
{
	return new Orc(0, 0, 1.6, game);
}
