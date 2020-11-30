#pragma once
#include "Projectile.h"

/// <summary>
/// Clase que representa un proyectil de tipo Misil.
/// </summary>
class Missile : public Projectile
{
public:
	Missile(float x, float y, Game* game);
};

