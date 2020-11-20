#pragma once

#include "Turret.h"

/// <summary>
/// Clase base abstracta para implementar un patr�n
/// FactoryMethod. Representa una factor�a de torretas.
/// </summary>
class TurretFactory
{
public:
	TurretFactory(Game* game);

	virtual Turret* createTurret() = 0;

	Game* game;
};

