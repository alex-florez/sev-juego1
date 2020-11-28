#include "EnemyB.h"

EnemyB::EnemyB(float x, float y, float speed, Game* game)
	: Enemy("res/jugador.png", 35, 35, x, y, speed, game)
{
	// Animaciones
	this->aMovingLeft = new Animation("res/enemy1/run/run_left.png", 64, 54, 448, 54, 3, 7, true, game);
	this->aMovingRight = new Animation("res/enemy1/run/run_right.png", 64, 54, 448, 54, 3, 7, true, game);

	this->aDyingLeft = new Animation("res/enemy1/death/death-left.png", 64, 54, 448, 54, 1, 7, false, game);
	this->aDyingRight = new Animation("res/enemy1/death/death-right.png", 64, 54, 448, 54, 1, 7, false, game);

	/*this->aHurtLeft = new Animation("res/enemy3/hurt/hurt-left.png", 35, 40, 70, 40, 3, 2, false, game);
	this->aHurtRight = new Animation("res/enemy3/hurt/hurt-right.png", 35, 40, 70, 40, 3, 2, false, game);*/

	this->aAttackingLeft = new Animation("res/enemy1/attack/attack_left.png", 64, 54, 448, 54, 2, 7, false, game);
	this->aAttackingRight = new Animation("res/enemy1/attack/attack_right.png", 64, 54, 448, 54, 2, 7, false, game);

}
