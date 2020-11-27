#include "PowerUp.h"

PowerUp::PowerUp(string filename, float width, float height, int ticksAlive, float x, float y, Game* game)
	: Actor(filename, x, y, width, height, game)
{
	this->collected = false;
	this->used = false;
	this->blink = false;
	this->ticksAlive = ticksAlive;
	
}

void PowerUp::draw()
{
	
	bool mustDraw = true;
	if (blink) {
		if (!(this->ticksAlive % 10 >= 0 && this->ticksAlive % 10 <= 5))
			mustDraw = false;
	}


	if (mustDraw) {
		this->glowAnimation->update();
		if(!collected)
			this->glowAnimation->draw(x, y);
		Actor::draw();
	}

	
}

void PowerUp::update()
{
	this->ticksAlive--;
	this->blink = this->ticksAlive < 50;
	
}


