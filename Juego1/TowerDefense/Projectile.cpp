#include "Projectile.h"


Projectile::Projectile(float x, float y, Game* game)
	: Actor("res/bullet1.png", x, y, 10, 10, game) {
	
	vx = 0;
	vy = 0;

	speed = 16;
}

void Projectile::update() {
	x = x + vx;
	y = y + vy;
}

void Projectile::moveTo(float x, float y) {
	float diffX = x - this->x; // Diff Vector
	float diffY = y - this->y;

	float d = sqrt(diffX * diffX + diffY * diffY);

	float normalX = diffX / d; // Normalizar el vector para obtener la dirección
	float normalY = diffY / d;

	float moveX = normalX * speed; // Multiplicar la dirección por el speed.
	float moveY = normalY * speed;

	this->vx = moveX;
	this->vy = moveY;
}