#include "Enemy.h"

Enemy::Enemy(float x, float y, Game* game)
	: Actor("res/enemigo.png", x, y, 36, 40, game) {

	//vx = -1 * ENEMY_SPEED;
	vxIntelligence = -1;
	vx = vxIntelligence;

	vy = 0;

	aMoving = new Animation("res/enemigo_movimiento.png", width, height,
								108, 40, 6, 3, true, game);
	aDying = new Animation("res/enemigo_morir.png", width, height, 280, 40, 6, 8, false, game);
	animation = aMoving;

	state = game->stateMoving;

	this->nextPoint = new Point(15, 5);
	this->lastPoint = nullptr;
}



void Enemy::update() {
	// Actualizar la animación
	bool endAnimation = animation->update();
	
	if (endAnimation) { // Terminó la animación
		
		if (state == game->stateDying) { // Estaba muriendo
			state = game->stateDead;
		}
	}

	if (state == game->stateMoving) { // Moviendo
		animation = aMoving;
	}
	if (state == game->stateDying) { // Muriendo
		animation = aDying;
		vx = 0; // Hacemos que pare
	}

	if (state != game->stateDying) { // Si no se está muriendo...
		// Y se ha quedado parado
		if (vx == 0) {
			vxIntelligence = vxIntelligence * -1;
			vx = vxIntelligence;
		}
		if (outRight) {
			// Mover hacia la izquierda
			if (vxIntelligence > 0) {
				vxIntelligence = vxIntelligence * -1;
			}
			vx = vxIntelligence;
		}
		if (outLeft) {
			// Mover hacia la derecha
			if (vxIntelligence < 0) {
				vxIntelligence = vxIntelligence * -1;
			}
			vx = vxIntelligence;
		}
	}

	// Seguir la trayectoria
	Point* actualPoint = getPointPos(); // Posición actual en la matriz.

	if (this->nextPoint == nullptr) {
		this->x += this->vx;
	}
	else {
		if (!this->nextPoint->equals(actualPoint, 0)) {
			int horizontal = nextPoint->getX() - actualPoint->getX();
			int vertical = nextPoint->getY() - actualPoint->getY();
			
			if (horizontal < 0) {
				this->vx = -1 * ENEMY_SPEED;
			}

			if (horizontal > 0) {
				this->vx = ENEMY_SPEED;
			}

			if (horizontal == 0) {
				this->vx = 0;
			}

			if (vertical < 0) {
				this->vy = -1 * ENEMY_SPEED;
			}

			if (vertical > 0) {
				this->vy = ENEMY_SPEED;
			}

			if (vertical == 0) {
				this->vy = 0;
			}
		}
		else {
			this->nextPoint = this->path->getNextPoint(actualPoint, lastPoint);
			this->lastPoint = new Point(actualPoint->getX(), actualPoint->getY());
		}

		this->x += this->vx;
		this->y += this->vy;
	}

}


Point* Enemy::getPointPos() {
	int j = (int)(this->x / 40);
	int i = (int)(this->y / 40);

	return new Point(j, i);
}

void Enemy::draw() {
	animation->draw(x, y);
}

void Enemy::impacted() {
	if (state != game->stateDying) {
		state = game->stateDying;
	}
}