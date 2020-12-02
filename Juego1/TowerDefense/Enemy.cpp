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
			else if (state == EnemyState::ATTACKING) { // Terminó la animación de ataque
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
/// Método que modela la lógica de ataque de este enemigo contra
/// la torre pasada como parámetro.
/// </summary>
/// <param name="tower">Torre que está siendo atacada.</param>
void Enemy::attack(Tower* tower) {
	if(this->state != EnemyState::DYING && this->state != EnemyState::DEAD)
		this->state = EnemyState::ATTACKING;
	this->targetTower = tower;
}

bool Enemy::impactedBy(Projectile* projectile) {
	bool dead = false;
	this->health -= projectile->damage;
	
	if (this->health <= 0 && this->state != EnemyState::DYING) {
		this->state = EnemyState::DYING;
		dead = true;
	}

	return dead;
}