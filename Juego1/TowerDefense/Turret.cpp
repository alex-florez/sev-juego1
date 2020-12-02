#include "Turret.h"


Turret::Turret(string filename, float x, float y, 
	float width, float height, int cost, Game* game)
	: Actor(filename, x, y, width, height, game) {

	this->id = -1;
	this->ticksUntilNextShoot = this->shootCadency;
	this->cost = cost;
	this->killedEnemies = 0;
	this->state = TurretState::PURCHASED;

	this->constructionAnimation = new Animation("res/smokeAnim.png", 56, 56, 392, 56, 1, 7, false, game);
	this->canBeUpgradedAnimation = new Animation("res/blue_glow.png", 70, 70, 1330, 70, 1, 19, true, game);

	this->canBeUpgraded = false;
}

void Turret::update(list<Enemy*>& enemies) {

	// Comprobar si la torreta se puede UPGRADEAR
	if (this->killedEnemies >= this->killedEnemiesForUpgrade) {
		this->canBeUpgraded = true;
	}

	if (this->currentTarget != nullptr // Si ya hay un enemigo objetivo,
		&& !isInArea(this->currentTarget)) { //  comprobar que no se haya salido del área de efecto
		this->currentTarget = nullptr;
	}

	if (this->state == TurretState::BUILT 
		|| this->state == TurretState::UPGRADED) { // Si la torreta ya está construida o mejorada
		// Escanear en busca de enemigos.
		scan(enemies);
		// Calcular el ángulo que debe rotar la torreta.
		this->angle = this->calculateAngleOfRotation();
	}
	else if (this->state == TurretState::BUILDING) { // Si la torreta se está construyendo
		bool finished = this->constructionAnimation->update();
		if (finished) {
			this->state = TurretState::BUILT;
		}
			
	}

	// Si la torreta puede mejorarse y no está en estado UPGRADED...
	// Actualizar la animación de upgrade.
	if (canBeUpgraded && state != TurretState::UPGRADED) {
		this->canBeUpgradedAnimation->update();
	}
	
}


list<Projectile*> Turret::shoot() {
	this->ticksUntilNextShoot--;
	Projectile* p1 = nullptr;
	Projectile* p2 = nullptr;

	list<Projectile*> projectiles;

	if (this->ticksUntilNextShoot <= 0) { // Se puede disparar
		if (this->currentTarget != nullptr) { // Obtener la posición del objetivo actual
			float targetX = this->currentTarget->x;
			float targetY = this->currentTarget->y;

			if (this->state == TurretState::UPGRADED) { // TORRETA UPGRADEADA CON DOS CAÑONES
				p1 = this->projectileFactory->createProjectile();
				p2 = this->projectileFactory->createProjectile();

				p1->turretId = this->id; // Asignarle al proyectil el id de esta torreta
				p2->turretId = this->id;

				// Establecer la posición de los proyectiles en los cañones de la torreta
				p1->x = x;
				p1->y = y + this->upgradedYCannonOffsets[0];

				p2->x = x;
				p2->y = y + this->upgradedYCannonOffsets[1];

				p1->updateAngle(this->angle);
				p2->updateAngle(this->angle);

				p1->moveTo(targetX, targetY);
				p2->moveTo(targetX, targetY);

				projectiles.push_back(p1);
				projectiles.push_back(p2);
			}
			else { // TORRETA NORMAL CON UN SOLO CAÑÓN
				p1 = this->projectileFactory->createProjectile();
				p1->turretId = this->id;
				p1->x = x;
				p1->y = y + this->yCannonOffset;
				p1->updateAngle(this->angle);
				p1->moveTo(targetX, targetY);
				
				projectiles.push_back(p1);
			}

			this->ticksUntilNextShoot = this->shootCadency;
			// Reproducir sonido
			shotSound->play();
		}
	}
	return projectiles;
}


void Turret::scan(list<Enemy*>& enemies) {
	float minDistance = INFINITY;
	Enemy* closestEnemy = nullptr;
	for (auto const& enemy : enemies) {
		float dist = distance(x, y, enemy->x, enemy->y);
		if (isInArea(enemy) && dist < minDistance 
			&& enemy->state != Enemy::EnemyState::DYING && enemy->state != Enemy::EnemyState::DEAD) {
			minDistance = dist;
			closestEnemy = enemy;
		}
	}
	this->currentTarget = closestEnemy;
}


float Turret::distance(float x1, float y1, float x2, float y2) {
	int dx = x2 - x1;
	int dy = y2 - y1;
	return sqrt(dx*dx + dy*dy);

}

float Turret::calculateAngleOfRotation() {
	if (this->currentTarget != nullptr) {
		float diffX = this->currentTarget->x - this->x;
		float diffY = this->currentTarget->y - this->y;
		return (atan2(diffY, diffX) * 180.0000) / 3.1416;
	}
	return 0.0;
}

bool Turret::isInArea(Enemy* enemy) {
	float thisLeft = this->x - TILE_WIDTH * this->xDetectionRange;
	float thisRight = this->x + TILE_WIDTH * this->xDetectionRange;
	float thisTop = this->y - TILE_HEIGHT * this->yDetectionRange;
	float thisBottom = this->y + TILE_HEIGHT * this->yDetectionRange;
	
	float eLeft = enemy->x - enemy->width / 2;
	float eRight = enemy->x + enemy->width / 2;
	float eTop = enemy->y - enemy->height / 2;
	float eBottom = enemy->y + enemy->height / 2;

	return eLeft <= thisRight && eRight >= thisLeft
		&& eBottom >= thisTop && eTop <= thisBottom;
}

void Turret::draw() {
	if (this->state == TurretState::BUILDING) {
		this->constructionAnimation->draw(x, y);
	}
	// Animación de Upgrade
	if (this->canBeUpgraded && this->state != TurretState::UPGRADED) {
		this->canBeUpgradedAnimation->draw(x, y);
	}

	Actor::draw();
}



