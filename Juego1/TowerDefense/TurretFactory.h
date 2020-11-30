#pragma once

#include "Turret.h"

#define CANNON_COST 0
#define MG_COST 0
#define MISSILE_LAUNCHER_COST 0


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

