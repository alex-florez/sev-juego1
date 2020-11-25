#pragma once

#include "TurretB.h"
#include "TurretFactory.h"

class TurretBFactory : public TurretFactory
{
public:
	TurretBFactory(Game* game);

	int getCost() override;
	Actor* getIcon() override;
	Turret* createTurret() override;

};

