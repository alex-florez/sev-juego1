#pragma once
#include "Projectile.h"
#include "Animation.h"

/// <summary>
/// Clase que representa un proyectil de tipo Misil.
/// </summary>
class Missile : public Projectile
{
public:
	Missile(float x, float y, Game* game);
	void draw() override;
	void updateAngle(float angle) override;

	Animation* flames;

};

