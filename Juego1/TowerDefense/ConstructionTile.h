#pragma once

#include "Actor.h"

/// <summary>
/// Clase que modela un tile en el cual se puede
/// construir una torreta.
/// </summary>
class ConstructionTile : public Actor
{
public:
	ConstructionTile(float x, float y, Game* game);

	bool occupied;
};

