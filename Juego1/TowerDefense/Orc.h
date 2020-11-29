#pragma once
#include "Enemy.h"

/// <summary>
/// Enemigo que representa un Orco.
/// </summary>
class Orc : public Enemy
{
public:
	Orc(float x, float y, float speed, Game* game);

};

