#include "MagentaGem.h"

MagentaGem::MagentaGem(float x, float y, int ticksAlive, Game* game)
	: Gem("res/mGem.png", value = 60, ticksAlive, 30, 32, x, y, game)
{

}
