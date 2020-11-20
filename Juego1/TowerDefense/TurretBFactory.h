#pragma once

#include "TurretB.h"
#include "TurretFactory.h"

class TurretBFactory : public TurretFactory
{
public:
	TurretBFactory(Game* game);

	Turret* createTurret() override;

};

