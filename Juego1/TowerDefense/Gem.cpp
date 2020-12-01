#include "Gem.h"


Gem::Gem(string filename, int value, int ticksAlive, float width, float height, float x, float y, Game* game)
	: Actor(filename, x, y, width, height, game) {

	this->value = value;
	this->collected = false;
	this->ticksAlive = ticksAlive;
	this->blink = false;
	this->glowAnimation = new Animation("res/blue_glow.png", 70, 70, 1330, 70, 1, 19, true, game);
	this->pickUpSound = new SoundEffect("res/sounds/gem_pickup.wav");
}

void Gem::update() {
	this->ticksAlive--;
	this->blink = ticksAlive < 50;
}

void Gem::draw() {
	bool mustDraw = true;
	if (blink) {
		if (!(this->ticksAlive % 10 >= 0 && this->ticksAlive % 10 <= 5)) {
			mustDraw = false;
		}
	}

	if (mustDraw) {
		this->glowAnimation->update();
		this->glowAnimation->draw(x, y);
		Actor::draw();
	}
}

