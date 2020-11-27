#include "Projectile.h"


Projectile::Projectile(string filename, float width, float height, int speed, int damage, float x, float y, Game* game)
	: Actor(filename, x, y, width, height, game) {
	
	vx = 16;
	vy = 0;

	this->speed = speed;
	this->damage = damage;
	this->impacted = false;
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