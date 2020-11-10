#include "Projectile.h"


Projectile::Projectile(float x, float y, Game* game)
	: Actor("res/disparo_jugador2.png", x, y, 20, 20, game) {
	
	vx = 0;
	vy = 0;
}

void Projectile::update() {
	//vy = vy - 1; // La gravedad suma 1 en cada tick, para anularla restamos uno.
	x = x + vx;
	y = y + vy;
}

void Projectile::moveTo(float x, float y) {
	float diffX = x - this->x;
	float diffY = y - this->y;

	float d = sqrt(diffX * diffX + diffY * diffY);

	float normalX = diffX / d;
	float normalY = diffY / d;

	float moveX = normalX * 5;
	float moveY = normalY * 5;

	this->vx = round(normalX * 5);
	this->vy = round(normalY * 5);
}