#pragma once

#include "Game.h"
#include "Point.h"

class Actor
{
public:
	Actor(string filename, float x, float y, int width, int height, Game* game);
	~Actor();
	virtual void draw();
	bool isOverlap(Actor* actor);
	bool isInRender();
	Point* getMatrixPoint();


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

	// Paths
	// Id de la trayectoria que debe seguir este actor o -1 si no sigue ninguna.
	int pathId;
	// Siguiente punto al que se debe desplazar el actor o null si no debe seguir una trayectoria.
	Point* nextPoint; 
	// �ltimo punto de la matriz en la que se encontraba el actor.
	Point* lastPoint;


};

