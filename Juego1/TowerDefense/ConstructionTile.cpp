#include "ConstructionTile.h"


ConstructionTile::ConstructionTile(float x, float y, Game* game)
	: Actor("res/construction_tile.png", x, y, 40, 40, game) {

	this->occupied = false;
}