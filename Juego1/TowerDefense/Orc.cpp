#include "Orc.h"

Orc::Orc(float x, float y, float speed, Game* game)
	: Enemy("", 35, 35, x, y, speed, game)
{
	// Animaciones
	this->aMovingLeft = new Animation("res/orc/run/run_left.png", 64, 44, 448, 44, 2, 7, true, game);
	this->aMovingRight = new Animation("res/orc/run/run_right.png", 64, 44, 448, 44, 2, 7, true, game);

	this->aDyingLeft = new Animation("res/orc/death/death_left.png", 64, 41, 448, 41, 1, 7, false, game);
	this->aDyingRight = new Animation("res/orc/death/death_right.png", 64, 41, 448, 41, 1, 7, false, game);

	this->aAttackingLeft = new Animation("res/orc/attack/attack_left.png", 64, 61, 448, 61, 4, 7, false, game);
	this->aAttackingRight = new Animation("res/orc/attack/attack_right.png", 64, 61, 448, 61, 4, 7, false, game);

	// Características del enemigo
	this->attackPower = 40;
	this->health = 240;

	this->hitSound = new SoundEffect("res/sounds/orchit.wav");

	this->killResources = ORC_KILL_RESOURCES;
}
