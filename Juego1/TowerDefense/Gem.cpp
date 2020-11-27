#include "Gem.h"


Gem::Gem(string filename, int value, int ticksAlive, float width, float height, float x, float y, Game* game)
	: Actor(filename, x, y, width, height, game) {

	this->value = value;
	this->collected = false;
	this->ticksAlive = ticksAlive;
	this->blink = true;
	this->glowAnimation = new Animation("res/blue_glow.png", 70, 70, 1330, 70, 1, 19, true, game);
}

void Gem::update() {
	this->ticksAlive--;
	this->blink = ticksAlive > 40 || ticksAlive % 8 == 0;
}

void Gem::draw() {
	if(blink){
		this->glowAnimation->update();
		this->glowAnimation->draw(x, y);
		Actor::draw();		
	}	
}

