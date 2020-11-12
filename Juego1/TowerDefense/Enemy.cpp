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

	this->attackFrequency = 50;
	this->ticksUntilNextAttack = 0;
}



void Enemy::update() {
	// Actualizar la animaci�n
	bool endAnimation = animation->update();
	
	if (endAnimation) { // Termin� la animaci�n
		
		//if (state == game->stateDying) { // Estaba muriendo
		//	state = game->stateDead;
		//}
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

	//if (state != game->stateDying) { // Si no se est� muriendo...
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

void Enemy::attack(Tower* tower) {
	if (this->state == ActorState::MOVING) {
		this->state = ActorState::ATTACKING;
		cout << "** Primer ataque" << endl;
		this->ticksUntilNextAttack = this->attackFrequency;
	}
	else if (this->state == ActorState::ATTACKING) {
		this->ticksUntilNextAttack--;
		if (this->ticksUntilNextAttack <= 0) {
			cout << "** Ataque sucesivo" << endl;
			this->ticksUntilNextAttack = this->attackFrequency;
		}
	}
	else {

	}
}

//void Enemy::impacted() {
//	if (state != game->stateDying) {
//		state = game->stateDying;
//	}
//}