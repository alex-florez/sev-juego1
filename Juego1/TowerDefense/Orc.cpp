#include "Orc.h"

Orc::Orc(float x, float y, float speed, Game* game)
	: Enemy("", 35, 35, x, y, speed, game)
{
	// Animaciones
	this->aMovingLeft = new Animation("res/orc/run/run_left.png", 64, 54, 448, 54, 3, 7, true, game);
	this->aMovingRight = new Animation("res/orc/run/run_right.png", 64, 54, 448, 54, 3, 7, true, game);

	this->aDyingLeft = new Animation("res/orc/death/death-left.png", 64, 54, 448, 54, 1, 7, false, game);
	this->aDyingRight = new Animation("res/orc/death/death-right.png", 64, 54, 448, 54, 1, 7, false, game);

	/*this->aHurtLeft = new Animation("res/enemy3/hurt/hurt-left.png", 35, 40, 70, 40, 3, 2, false, game);
	this->aHurtRight = new Animation("res/enemy3/hurt/hurt-right.png", 35, 40, 70, 40, 3, 2, false, game);*/

	this->aAttackingLeft = new Animation("res/orc/attack/attack_left.png", 64, 54, 448, 54, 3, 7, false, game);
	this->aAttackingRight = new Animation("res/orc/attack/attack_right.png", 64, 54, 448, 54, 3, 7, false, game);

	// Características del enemigo
	this->attackPower = 40;
	this->health = 200;

	this->hitSound = new SoundEffect("res/sounds/orchit.wav");
}
