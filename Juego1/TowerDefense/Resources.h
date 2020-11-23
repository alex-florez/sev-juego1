#pragma once

#include "Actor.h"

/// <summary>
/// Clase que modela un coleccionable de recursos
/// para el jugador.
/// </summary>
class Resources : public Actor
{
public:
	Resources(float x, float y, Game* game);

	int quantity;
	int collected;
};

