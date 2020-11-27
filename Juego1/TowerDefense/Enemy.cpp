#include "Enemy.h"

Enemy::Enemy(string filename, float width, float height, float x, float y, float speed, Game* game)
	: Pawn(filename, width, height, x, y, speed, game) {

	//vx = -1 * ENEMY_SPEED;
	vx = 0;
	vy = 0;

	aMoving = new Animation("res/enemigo_movimiento.png", width, height,
								108, 40, 6, 3, true, game);
	aDying = new Animation("res/enemigo_morir.png", width, height, 280, 40, 6, 8, false, game);
	animation = aMoving;

	/*state = game->stateMoving;*/

	this->state = EnemyState::MOVING;
	//this->speed = speed;

	this->attackPower = 25;
	this->attackFrequency = 20;
	this->ticksUntilNextAttack = 0;

	this->health = 100;
}



void Enemy::update() {
	// Actualizar la animación
	bool endAnimation = animation->update();
	
	if (endAnimation) { // Terminó la animación
		
		if (state == EnemyState::DYING) { // Estaba muriendo
			state = EnemyState::DEAD;
		}
	}

	// Si el enemigo no está colisionando con algo que siga moviéndose
	//if (!isCollisioning) { 
	//	this->state = EnemyState::MOVING;
	//}

	if (state == EnemyState::MOVING) {
		animation = aMoving;
		this->stopFollowing = false;
	}
	else if (state == EnemyState::DYING) {
		animation = aDying;
		this->stopFollowing = true;
	}
	else if (state == EnemyState::ATTACKING) {
		this->stopFollowing = true;
	}

	this->x += this->vx;
	this->y += this->vy;
	
}



void Enemy::draw() {
	//animation->draw(x, y);
	Actor::draw();
}

/// <summary>
/// Método que modela la lógica de ataque de este enemigo contra
/// la torre pasada como parámetro.
/// </summary>
/// <param name="tower">Torre que está siendo atacada.</param>
void Enemy::attack(Tower* tower) {
	if (this->state == EnemyState::MOVING) { // El enemigo se estaba aproximando a la torre
		this->state = EnemyState::ATTACKING; // Enemigo realiza primer ataque.
		cout << "** Primer ataque " << tower->health << endl;
		this->ticksUntilNextAttack = 0;
	}
	else if (this->state == EnemyState::ATTACKING) {
		this->ticksUntilNextAttack--;
	}

	if (this->ticksUntilNextAttack <= 0) {
		tower->health -= this->attackPower;
		this->ticksUntilNextAttack = this->attackFrequency;
		if (tower->health <= 0) { // Si tras este último ataque la torre se destruye...
			this->state = EnemyState::MOVING; // El enemigo vuelve al estado MOVING
		}
	}
}

void Enemy::impactedBy(Projectile* projectile, Player* player) {
	this->health -= projectile->damage;
	if (this->health <= 0 && this->state != EnemyState::DYING) {
		this->state = EnemyState::DYING;
		// Incrementar recursos del jugador por haber eliminado al enemigo.
		player->availableResources += PLAYER_KILL_RESOURCES;
		player->killedEnemiesInActualHorde++;
	}
}