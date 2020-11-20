#include "Pawn.h"


Pawn::Pawn(string filename, int width, int height, float x, float y, float speed, Game* game)
	: Actor(filename, x, y, width, height, game) {

	this->speed = speed;
	this->lastPoint = new Point((int)(x / TILE_WIDTH), (int)(y / TILE_HEIGHT));
	this->nextPoint = nullptr;
	this->stopFollowing = false;
}

Point* Pawn::getActualPoint() {
	return new Point(
		(int)(this->x / TILE_WIDTH),
		(int)(this->y / TILE_HEIGHT)
	);
}

void Pawn::move() {
	if (this->nextPoint != nullptr) {
		float destX = this->nextPoint->getX() * TILE_WIDTH + TILE_WIDTH / 2;
		float destY = this->nextPoint->getY() * TILE_HEIGHT + TILE_HEIGHT / 2;

		float diffX = destX - this->x;
		float diffY = destY - this->y;

		float d = sqrt(diffX * diffX + diffY * diffY);

		float normalX = diffX / d;
		float normalY = diffY / d;

		this->vx = normalX * this->speed;
		this->vy = normalY * this->speed;
	}
}


bool Pawn::isAtDestiny() {
	//int xPoint = point->getX() * 40 + 20;
	//int yPoint = point->getY() * 40 + 20;

	//return this->x == xPoint && this->y == yPoint;

	int xPoint = (int)(this->x / TILE_WIDTH);
	int yPoint = (int)(this->y / TILE_HEIGHT);
	if(this->nextPoint != nullptr)
		return this->nextPoint->getX() == xPoint && this->nextPoint->getY() == yPoint;
	return false;
}