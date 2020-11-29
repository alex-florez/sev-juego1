#pragma once

#include "Enemy.h"

/// <summary>
/// Enemigo que representa una momia.
/// </summary>
class Mummy : public Enemy
{
public:
	Mummy(float x, float y, float speed, Game* game);
};

