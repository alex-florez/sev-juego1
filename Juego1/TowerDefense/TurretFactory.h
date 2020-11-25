#pragma once

#include "Turret.h"

#define TURRET_A_COST 200
#define TURRET_B_COST 500


/// <summary>
/// Clase base abstracta para implementar un patrón
/// FactoryMethod. Representa una factoría de torretas.
/// </summary>
class TurretFactory
{
public:
	TurretFactory(Game* game);

	virtual Turret* createTurret() = 0;
	virtual int getCost() = 0;
	virtual Actor* getIcon() = 0;

	Game* game;
};

