#pragma once

#include "Turret.h"

#define CANNON_COST 200
#define MG_COST 300
#define MISSILE_LAUNCHER_COST 300


/// <summary>
/// Clase base abstracta para implementar un patr�n
/// FactoryMethod. Representa una factor�a de torretas.
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

