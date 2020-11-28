#include "Enemy.h"

Enemy::Enemy(string filename, float width, float height, float x, float y, float speed, Game* game)
	: Pawn(filename, width, height, x, y, speed, game) {

	vx = 0;
	vy = 0;

	/*aMoving = new Animation("res/enemy3/run/run_left.png", 35, 40, 210, 40, 3, 6, true, game);
	aDying = new Animation("res/enemy3/death/death-left.png", 35, 40, 210, 40, 3, 6, false, game);
	aAttacking = new Animation("res/enemy3/attack/attack_left.png", 35, 40, 210, 40, 2, 6, true, game);*/
	animation = aMovingLeft;
	orientation = Orientation::LEFT;

	this->state = EnemyState::MOVING;
	
	this->attackPower = 25;
	this->attackFrequency = 20;
	this->ticksUntilNextAttack = 0;

	this->health = 100;
	this->hit = false;
}



void Enemy::update() {
	// Establecer orientación
	if (vx < 0)
		orientation = Orientation::LEFT;
	else if (vx > 0)
		orientation = Orientation::RIGHT;

	//if (vy < 0)
	//	orientation = Orientation::TOP;
	//if (vy > 0)
	//	orientation = Orientation::BOTTOM;

	// Establecer las animaciones en función del estado
	if (state == EnemyState::MOVING) {
		if (orientation == Orientation::LEFT)
			animation = aMovingLeft;
		else if (orientation == Orientation::RIGHT)
			animation = aMovingRight;

		this->stopFollowing = false;
		this->ticksUntilNextAttack = 0;
	}
	else if (state == EnemyState::DYING) {
		if (orientation == Orientation::LEFT)
			animation = aDyingLeft;
		else if (orientation == Orientation::RIGHT)
			animation = aDyingRight;
		this->stopFollowing = true;
	}
	else if (state == EnemyState::ATTACKING) {
		if (orientation == Orientation::LEFT)
			animation = aAttackingLeft;
		else if (orientation == Orientation::RIGHT)
			animation = aAttackingRight;
		this->stopFollowing = true;
		this->ticksUntilNextAttack--;
	}


	if (animation != nullptr) { // Actualizar la animación
		bool endAnimation = animation->update();

		if (endAnimation) { // Terminó la animación
			if (state == EnemyState::DYING) { // Estaba muriendo
				state = EnemyState::DEAD;
			}
			else if (this->hit) {
				state = EnemyState::MOVING;
				this->hit = false;
			}
		}

	}
		

	this->x += this->vx;
	this->y += this->vy;
	
}



void Enemy::draw() {
	animation->draw(x, y);
	//Actor::draw();
}

/// <summary>
/// Método que modela la lógica de ataque de este enemigo contra
/// la torre pasada como parámetro.
/// </summary>
/// <param name="tower">Torre que está siendo atacada.</param>
void Enemy::attack(Tower* tower) {
	this->state = EnemyState::ATTACKING;

	if (ticksUntilNextAttack <= 0) { // Si le toca atacar...
		tower->health -= this->attackPower;
		ticksUntilNextAttack = this->attackFrequency;
	}
}

void Enemy::impactedBy(Projectile* projectile, Player* player) {
	this->health -= projectile->damage;
	//
	//if (this->state != EnemyState::DYING && this->state != EnemyState::DEAD) {
	//	this->hit = true;
	//}

	if (this->health <= 0 && this->state != EnemyState::DYING) {
		this->state = EnemyState::DYING;
		// Incrementar recursos del jugador por haber eliminado al enemigo.
		player->availableResources += PLAYER_KILL_RESOURCES;
		player->killedEnemiesInActualHorde++;
	}
}