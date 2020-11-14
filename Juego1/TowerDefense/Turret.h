#pragma once

#include "Actor.h"

/// <summary>
/// Clase que hereda de Actor y que modela una torreta que
/// se puede construir en un ConstructionTile.
/// </summary>
class Turret : public Actor
{
public:
	Turret(string filename, float x, float y, float width, float height, Game* game);
};

