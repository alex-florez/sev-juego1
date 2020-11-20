#pragma once

#include "TurretFactory.h"
#include "TurretA.h"

class TurretAFactory : public TurretFactory
{
public:
	TurretAFactory(Game* game);

	Turret* createTurret() override;
	
};

