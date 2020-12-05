#include "BlueGem.h"

BlueGem::BlueGem(float x, float y, int ticksAlive, Game* game)
	: Gem("res/bGem.png", value = 40, ticksAlive, 31, 32, x, y, game)
{
}
