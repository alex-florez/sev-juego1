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

	this->nextPoint= new Point(19, 5);
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
			//vx = vxIntelligence;
		}
		if (outRight) {
			// Mover hacia la izquierda
			if (vxIntelligence > 0) {
				vxIntelligence = vxIntelligence * -1;
			}
			//vx = vxIntelligence;
		}
		if (outLeft) {
			// Mover hacia la derecha
			if (vxIntelligence < 0) {
				vxIntelligence = vxIntelligence * -1;
			}
			//vx = vxIntelligence;
		}
	}
		this->x += this->vx;
		this->y += this->vy;
	
}

bool Enemy::checkInsideCell(Point* cellCenter, float error) {
	int xCenter = cellCenter->getX() * 40 + 20;
	int yCenter = cellCenter->getY() * 40 - 20;

	return x >= xCenter - error && x <= xCenter + error
		&& y >= yCenter - error && y <= yCenter + error;
}




void Enemy::draw() {
	animation->draw(x, y);
}

void Enemy::impacted() {
	if (state != game->stateDying) {
		state = game->stateDying;
	}
}