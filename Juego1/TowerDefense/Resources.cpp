#include "Resources.h"


Resources::Resources(float x, float y, Game* game)
	: Actor("res/asteroide.png", x, y, 50, 51, game) {

	this->quantity = 50;
	this->collected = false;
}