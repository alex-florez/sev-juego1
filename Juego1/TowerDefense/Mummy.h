#pragma once

#include "Enemy.h"

#define MUMMY_KILL_RESOURCES 50

/// <summary>
/// Enemigo que representa una momia.
/// </summary>
class Mummy : public Enemy
{
public:
	Mummy(float x, float y, float speed, Game* game);
};

