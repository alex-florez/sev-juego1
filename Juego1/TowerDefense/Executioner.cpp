#include "Executioner.h"

Executioner::Executioner(float x, float y, float speed, Game* game)
	: Enemy("", 31, 36, x, y, speed, game)
{
	// Animaciones
	this->aMovingLeft = new Animation("res/executioner/run/run_left.png", 47, 65, 376, 65, 1, 8, true, game);
	this->aMovingRight = new Animation("res/executioner/run/run_right.png", 47, 65, 376, 65, 1, 8, true, game);

	this->aDyingLeft = new Animation("res/executioner/death/death_left.png", 57, 70, 1026, 70, 1, 18, false, game);
	this->aDyingRight = new Animation("res//death/death_right.png", 57, 70, 1026, 70, 1, 18, false, game);

	this->aAttackingLeft = new Animation("res/executioner/attack/attack_left_1.png", 68, 78, 476, 78, 2, 7, false, game);
	this->aAttackingRight = new Animation("res/executioner/attack/attack_right_1.png", 68, 78, 476, 78, 2, 7, false, game);

	// Características del enemigo
	this->attackPower = 45;
	this->health = 100;

	this->hitSound = new SoundEffect("res/sounds/sword.wav");

	this->killResources = EXECUTIONER_KILL_RESOURCES;
}
