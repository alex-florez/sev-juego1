#pragma once

#include "Actor.h"
#include "Point.h"

/// <summary>
/// Clase que representa un Actor que es controlable,
/// es decir, sigue una trayectoria predefinida en el mapa.
/// </summary>
class Pawn : public Actor
{
public:
	Pawn(string filename, int width, int height, float x, float y, float speed, Game* game);
	/// <summary>
	/// Devuelve la posición actual de este Pawn en la 
	/// matriz del mapa.
	/// </summary>
	/// <returns>Punto en la matriz del mapa</returns>
	Point* getActualPoint();

	/// <summary>
	/// Método encargado de dirigir al Pawn al siguiente 
	/// punto de destino.
	/// </summary>
	void move();

	/// <summary>
	/// Indica si el pawn se encuentra en el punto del mapa
	/// marcado como su destino.
	/// </summary>
	/// <returns>true si se encuentra en el punto</returns>
	bool isAtDestiny();



	int pathId; // Id del camino que debe seguir este Pawn
	Point* nextPoint; // Siguiente punto al que debe dirigirse el pawn.
	Point* lastPoint; // Último punto del que proviene el pawn.
	bool stopFollowing; // Flag para indicar si el pawn debe dejar de seguir la trayectoria.
	int speed; // Velocidad del pawn.
};

