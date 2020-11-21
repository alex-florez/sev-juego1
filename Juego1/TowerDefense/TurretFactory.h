#pragma once

#include "Turret.h"

/// <summary>
/// Clase base abstracta para implementar un patrón
/// FactoryMethod. Representa una factoría de torretas.
/// </summary>
class TurretFactory
{
public:
	TurretFactory(Game* game);

	virtual Turret* createTurret() = 0;

	Game* game;
	Actor* iconView; // Representa un icono con la miniatura de la torreta.
};

