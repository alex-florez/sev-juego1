#pragma once

#include "MG.h"
#include "TurretFactory.h"

class MGFactory : public TurretFactory
{
public:
	MGFactory(Game* game);

	int getCost() override;
	Actor* getIcon() override;
	Turret* createTurret() override;

};

