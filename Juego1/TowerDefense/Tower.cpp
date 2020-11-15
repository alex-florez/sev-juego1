#include "Tower.h"


Tower::Tower(string filename, float x, float y, Game* game)
	: Actor(filename, x, y, 60, 69, game) {

	this->health = 100;
	this->state = TowerState::ALIVE;
	this->explotionAnim = new Animation("res/tower_explosion.png", 60, 56, 480, 56, 2, 8, false, game);
}


void Tower::update() {
	if (health <= 0) {
		this->state = TowerState::EXPLODING;
	}

	if (this->state == TowerState::EXPLODING) {
		bool endExploding = explotionAnim->update();
		if (endExploding) {  // Torre termina de explotar.
			this->state = TowerState::DESTROYED;
		}
	}
}

void Tower::draw() {
	if (state == TowerState::ALIVE) {
		Actor::draw();
	}
	else if (state == TowerState::EXPLODING) {
		explotionAnim->draw(x, y);
	}
}