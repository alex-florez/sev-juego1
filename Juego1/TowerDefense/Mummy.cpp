#include "Mummy.h"

Mummy::Mummy(float x, float y, float speed, Game* game)
	: Enemy("", 36, 40, x, y, speed, game)
{
	// Animaciones
	this->aMovingLeft = new Animation("res/mummy/run/run_left.png", 35, 40, 210, 40, 3, 6, true, game);
	this->aMovingRight = new Animation("res/mummy/run/run_right.png", 35, 40, 210, 40, 3, 6, true, game);

	this->aDyingLeft = new Animation("res/mummy/death/death-left.png", 35, 40, 210, 40, 3, 6, false, game);
	this->aDyingRight = new Animation("res/mummy/death/death-right.png", 35, 40, 210, 40, 3, 6, false, game);

	this->aAttackingLeft = new Animation("res/mummy/attack/attack_left.png", 35, 40, 210, 40, 2, 6, false, game);
	this->aAttackingRight = new Animation("res/mummy/attack/attack_right.png", 35, 40, 210, 40, 2, 6, false, game);

	// CaracterÝsticas del enemigo
	this->attackPower = 12;
	this->health = 120;

	this->hitSound = new SoundEffect("res/sounds/crack07.wav");

	this->killResources = MUMMY_KILL_RESOURCES;
}
