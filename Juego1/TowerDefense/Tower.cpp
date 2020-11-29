#include "Tower.h"


Tower::Tower(string filename, float x, float y, Game* game)
	: Actor(filename, x, y, 60, 69, game) {

	this->health = TOWER_INITIAL_HEALTH;
	this->uiHealth = new UITextIcon(x - this->width/2, y - this->height - 15, 30, 30, 42,
		new RGB(0, 255 ,255), "res/healthIcon.png", to_string(this->health), game);
	this->state = TowerState::ALIVE;
	this->explotionAnim = new Animation("res/tower_explosion.png", 60, 56, 480, 56, 2, 8, false, game);
	this->powerUpEffectAnimation = new Animation("res/GreenSlash.png", 64, 64, 256, 64, 1, 4, false, game);
	this->destroyedGround = new Actor("res/destroyedGround.png", x, y - 20, 70, 50, game);
	this->repairIcon = new UIRepairIcon(x, y-34, TOWER_REPAIR_COST, game);
	this->applyingPowerUp = false;
}


void Tower::update() {
	if (applyingPowerUp) { // Se le está aplicando una mejora
		applyingPowerUp = !this->powerUpEffectAnimation->update(); // Comprobar si termina la animación
	}

	if (health <= 0) {
		if(this->state == TowerState::ALIVE)
			this->state = TowerState::EXPLODING;
	}

	if (this->state == TowerState::EXPLODING) {
		bool endExploding = explotionAnim->update();
		if (endExploding) {  // Torre termina de explotar.
			this->state = TowerState::DESTROYED;
		}
	}
	this->uiHealth->text->content = to_string(this->health);
}

void Tower::draw() {
	this->destroyedGround->draw();
	if (state == TowerState::ALIVE) {
		Actor::draw();
		this->uiHealth->draw();
		if (this->applyingPowerUp) {
			this->powerUpEffectAnimation->draw(x, y);
		}
	}
	else if (state == TowerState::EXPLODING) {
		explotionAnim->draw(x, y);
	}
	else if (state == TowerState::DESTROYED) {
		this->repairIcon->draw();
	}
}

void Tower::repair() {
	this->state = TowerState::REPAIRED;
	this->health = TOWER_INITIAL_HEALTH;
}

void Tower::hit(float damage)
{
	this->health -= damage;
}
