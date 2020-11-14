#pragma once

#include "Game.h"
#include "Point.h"


class Actor
{
public:

	/// <summary>
	/// Enumerado que define los estados de un enemigo:
	///		* MOVING: se est� moviendo siguiendo la trayectoria que le corresponde.
	///		* ATTACKING: est� atacando a una de las torres.
	/// </summary>
	enum class ActorState { MOVING, ATTACKING };

	Actor(string filename, float x, float y, int width, int height, Game* game);
	~Actor();
	virtual void draw();
	bool isOverlap(Actor* actor);
	bool isInRender();
	Point* getMatrixPoint();
	bool isInPoint(Point* point);


	// Control con el rat�n
	bool containsPoint(int pointX, int pointY); // Contiene punto?
	bool clicked;



	bool collisionDown; // Indica si el actor est� colisionando por abajo.
	bool outRight; // Indica si el actor se sale por la derecha
	bool outLeft; // Actor se sale por la izquierda.

	bool invisible; // Indica si el actor es afectado por las colisiones o es atravesable.

	SDL_Texture* texture;
	// Posici�n
	float x;
	float y;
	// Velocidad
	float vx;
	float vy;
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

	float speed;
	ActorState state;
};

