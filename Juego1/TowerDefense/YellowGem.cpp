#include "YellowGem.h"

YellowGem::YellowGem(float x, float y, int ticksAlive, Game* game)
	: Gem("res/yGem.png", value = 80, ticksAlive, 31, 32, x, y, game)
{
}
