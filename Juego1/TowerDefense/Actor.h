#pragma once

#include "Game.h"

class Actor
{
public:
	Actor(string filename, float x, float y, int width, int height, Game* game);
	~Actor();
	virtual void draw(float scrollX = 0, float scrollY = 0);
	bool isOverlap(Actor* actor);
	bool isInRender(float scrollX = 0, float scrollY = 0);

	// Control con el rat�n
	bool containsPoint(int pointX, int pointY); // Contiene punto?
	bool clicked;



	bool collisionDown; // Indica si el actor est� colisionando por abajo.
	bool outRight; // Indica si el actor se sale por la derecha
	bool outLeft; // Actor se sale por la izquierda.

	SDL_Texture* texture;
	// Posici�n
	int x;
	int y;
	// Velocidad
	int vx;
	int vy;
	// Tama�o en el juego
	int width;
	int height;
	// Tama�o de la imagen real
	int fileWidth;
	int fileHeight;
	
	Game* game;

};

