#pragma once
#include "Enemy.h"

#define ORC_KILL_RESOURCES 100

/// <summary>
/// Enemigo que representa un Orco.
/// </summary>
class Orc : public Enemy
{
public:
	Orc(float x, float y, float speed, Game* game);

};

