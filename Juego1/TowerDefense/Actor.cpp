#include "Actor.h"

Actor::Actor(string filename, float x, float y, int width, int height, Game* game) {
	this->game = game;
	// Creamos la textura: la buscamos en la cache de texturas
	texture = game->getTexture(filename);
	this->x = x;
	this->y = y;
	// Lo que mide el fichero
	this->fileWidth = width;
	this->fileHeight = height;
	// Lo que mide en el juego
	this->width = width;
	this->height = height;
	// Control del ratón
	clicked = false;
	this->filename = filename;
	this->angle = 0;
}


Actor::~Actor() {
	
}


void Actor::draw() {
	// Recorte en el fichero de la imagen
	SDL_Rect source;
	source.x = 0;
	source.y = 0;
	source.w = fileWidth; // texture.width
	source.h = fileHeight; // texture.height

	// Donde se va a pegar en el renderizador
	SDL_Rect destination;
	float destX = x - width / 2;
	float destY = y - height / 2;
	//cout << "destX: " << destX << " destY: " << destY << endl;
	destination.x = round(destX);
	destination.y = round(destY);
	destination.w = width;
	destination.h = height;
	// Modificar para que la referencia sea el punto central.
	SDL_RenderCopyEx(game->renderer, texture, &source, &destination, this->angle, NULL, SDL_FLIP_NONE);
}

bool Actor::isOverlap(Actor* actor) {
	bool overlap = false;
	if (actor->x - actor->width/2 <= x + width/2
		&& actor->x + actor->width/2 >= x - width/2
		&& actor->y + actor->height/2 >= y - height/2
		&& actor->y - actor->height/2 <= y + height/2) {
		
		overlap = true;
	}

	return overlap;
}

bool Actor::isInRender()
{
	if (x - width / 2  <= WIDTH && x + width / 2 >= 0 &&
		y - height / 2 <= HEIGHT && y + height / 2 >= 0) {
		return true;
	}
	return false;
}

bool Actor::containsPoint(int pointX, int pointY) {
	if (pointY >= y - height / 2 &&
		pointY <= y + height / 2 &&
		pointX >= x - width / 2 &&
		pointX <= x + width / 2) {
		return true;
	}
	return false;
}