#include "Enemy.h"

Enemy::Enemy(float x, float y, float speed, Game* game)
	: Actor("res/enemigo.png", x, y, 36, 40, game) {

	//vx = -1 * ENEMY_SPEED;
	vx = 0;
	vy = 0;

	aMoving = new Animation("res/enemigo_movimiento.png", width, height,
								108, 40, 6, 3, true, game);
	aDying = new Animation("res/enemigo_morir.png", width, height, 280, 40, 6, 8, false, game);
	animation = aMoving;

	/*state = game->stateMoving;*/

	this->state = ActorState::MOVING;
	this->speed = speed;

	this->attackFrequency = 30;
	this->ticksUntilNextAttack = 0;
}



void Enemy::update() {
	// Actualizar la animación
	bool endAnimation = animation->update();
	
	if (endAnimation) { // Terminó la animación
		
		//if (state == game->stateDying) { // Estaba muriendo
		//	state = game->stateDead;
		//}
	}

	// Si el enemigo no está colisionando con algo que siga moviéndose
	if (!isCollisioning) { 
		this->state = ActorState::MOVING;
	}

	//if (state == game->stateMoving) { // Moviendo
	//	animation = aMoving;
	//}
	if (state == ActorState::MOVING) {
		animation = aMoving;
	}

	//if (state == game->stateDying) { // Muriendo
	//	animation = aDying;
	//	vx = 0; // Hacemos que pare
	//}

	//if (state != game->stateDying) { // Si no se está muriendo...
	//	// Y se ha quedado parado
	//	if (vx == 0) {
	//		
	//		//vx = vxIntelligence;
	//	}
	//	if (outRight) {
	//		// Mover hacia la izquierda
	//		//vx = vxIntelligence;
	//	}
	//	if (outLeft) {
	//		// Mover hacia la derecha
	//		//vx = vxIntelligence;
	//	}
	//}
		this->x += this->vx;
		this->y += this->vy;
	
}

//bool Enemy::checkInsideCell(Point* cellCenter, float error) {
//	int xCenter = cellCenter->getX() * 40 + 20;
//	int yCenter = cellCenter->getY() * 40 - 20;
//
//	return x >= xCenter - error && x <= xCenter + error
//		&& y >= yCenter - error && y <= yCenter + error;
//}


void Enemy::draw() {
	animation->draw(x, y);
}

/// <summary>
/// Método que modela la lógica de ataque de este enemigo contra
/// la torre pasada como parámetro.
/// </summary>
/// <param name="tower">Torre que está siendo atacada.</param>
void Enemy::attack(Tower* tower) {
	if (this->state == ActorState::MOVING) { // El enemigo se estaba aproximando a la torre
		this->state = ActorState::ATTACKING; // Enemigo realiza primer ataque.
		cout << "** Primer ataque " << tower->health << endl;
		this->ticksUntilNextAttack = 0;
	}
	else if (this->state == ActorState::ATTACKING) {
		this->ticksUntilNextAttack--;
	}

	if (this->ticksUntilNextAttack <= 0) {
		tower->health -= 30;
		this->ticksUntilNextAttack = this->attackFrequency;
	}
}

//void Enemy::impacted() {
//	if (state != game->stateDying) {
//		state = game->stateDying;
//	}
//}