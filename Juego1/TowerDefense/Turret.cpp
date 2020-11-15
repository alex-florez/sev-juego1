#include "Turret.h"


Turret::Turret(string filename, float x, float y, 
	float width, float height, Game* game)
	: Actor(filename, x, y, width, height, game) {



	this->shootCadency = 30;
	this->ticksUntilNextShoot = this->shootCadency;

	this->xDetectionRange = 4;
	this->yDetectionRange = 4;
}

void Turret::update() {
	if (this->currentTarget != nullptr // Si ya hay un enemigo objetivo,
		&& !isInArea(this->currentTarget)) { //  comprobar que no se haya salido del área de efecto
		this->currentTarget = nullptr;
	}
}



Projectile* Turret::shoot(list<Enemy*>& enemies) {
	this->ticksUntilNextShoot--;
	Projectile* p = nullptr;
	if (this->ticksUntilNextShoot <= 0) { // Se puede disparar
		scan(enemies); // Escaneamos los enemigos para obtener el más cercano dentro del árera de efecto.
		if (this->currentTarget != nullptr) { // Obtener la posición del objetivo actual
			p = new Projectile(x, y, game);
			float targetX = this->currentTarget->x;
			float targetY = this->currentTarget->y;
			p->moveTo(targetX, targetY);
			this->ticksUntilNextShoot = this->shootCadency;
		}
	}
	return p;
}


void Turret::scan(list<Enemy*>& enemies) {
	float minDistance = INFINITY;
	Enemy* closestEnemy = nullptr;
	for (auto const& enemy : enemies) {
		float dist = distance(x, y, enemy->x, enemy->y);
		if (isInArea(enemy) && dist < minDistance 
			&& enemy->state != ActorState::DYING && enemy->state != ActorState::DEAD) {
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