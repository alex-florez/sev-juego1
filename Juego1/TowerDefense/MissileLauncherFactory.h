#pragma once
#include "TurretFactory.h"
#include "MissileLauncher.h"

class MissileLauncherFactory : public TurretFactory
{
public:
	MissileLauncherFactory(Game* game);

	int getCost() override;
	Actor* getIcon() override;
	Turret* createTurret() override;
};

