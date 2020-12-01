#include "Enemy.h"

Enemy::Enemy(string filename, float width, float height, float x, float y, float speed, Game* game)
	: Pawn(filename, width, height, x, y, speed, game) {

	vx = 0;
	vy = 0;

	animation = aMovingLeft;
	orientation = Orientation::LEFT;

	this->state = EnemyState::MOVING;
	
	
	this->attackFrequency = 20;
	this->ticksUntilNextAttack = 0;

	this->hit = false;
	this->targetTower = nullptr;

}



void Enemy::update() {
	// Establecer orientaci�n
	if (vx < 0)
		orientation = Orientation::LEFT;
	else if (vx > 0)
		orientation = Orientation::RIGHT;

	//if (vy < 0)
	//	orientation = Orientation::TOP;
	//if (vy > 0)
	//	orientation = Orientation::BOTTOM;

	// Establecer las animaciones en funci�n del estado
	if (state == EnemyState::MOVING) {
		if (orientation == Orientation::LEFT)
			animation = aMovingLeft;
		else if (orientation == Orientation::RIGHT)
			animation = aMovingRight;

		this->stopFollowing = false;
		this->ticksUntilNextAttack = 0;
		this->targetTower = nullptr;
	}
	else if (state == EnemyState::DYING) {
		if (orientation == Orientation::LEFT)
			animation = aDyingLeft;
		else if (orientation == Orientation::RIGHT)
			animation = aDyingRight;
		this->stopFollowing = true;
		this->targetTower = nullptr;
	}
	else if (state == EnemyState::ATTACKING) {
		if (orientation == Orientation::LEFT)
			animation = aAttackingLeft;
		else if (orientation == Orientation::RIGHT)
			animation = aAttackingRight;
		this->stopFollowing = true;
		this->ticksUntilNextAttack--;
	}


	if (animation != nullptr) { // Actualizar la animaci�n
		bool endAnimation = animation->update();

		if (endAnimation) { // Termin� la animaci�n
			if (state == EnemyState::DYING) { // Estaba muriendo
				state = EnemyState::DEAD;
			}
			else if (this->hit) {
				state = EnemyState::MOVING;
				this->hit = false;
			}
			else if (state == EnemyState::ATTACKING) { // Termin� la animaci�n de ataque
				this->targetTower->hit(this->attackPower); // Decrementar la salud de la torre.
				// Reproducir sonido de golpe
				this->hitSound->play();
			}
		}

	}
		

	this->x += this->vx;
	this->y += this->vy;
	
}



void Enemy::draw() {
	animation->draw(x, y);
}

/// <summary>
/// M�todo que modela la l�gica de ataque de este enemigo contra
/// la torre pasada como par�metro.
/// </summary>
/// <param name="tower">Torre que est� siendo atacada.</param>
void Enemy::attack(Tower* tower) {
	if(this->state != EnemyState::DYING && this->state != EnemyState::DEAD)
		this->state = EnemyState::ATTACKING;
	this->targetTower = tower;
}

void Enemy::impactedBy(Projectile* projectile, Player* player) {
	
	this->health -= projectile->damage;
	
	if (this->health <= 0 && this->state != EnemyState::DYING) {
		this->state = EnemyState::DYING;
		// Incrementar recursos del jugador por haber eliminado al enemigo.
		player->addResources(PLAYER_KILL_RESOURCES);
		player->killedEnemiesInActualHorde++;
	}
}