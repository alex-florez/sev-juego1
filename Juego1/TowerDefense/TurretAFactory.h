#pragma once

#include "TurretFactory.h"
#include "TurretA.h"



class TurretAFactory : public TurretFactory
{
public:
	TurretAFactory(Game* game);

	int getCost() override;
	Actor* getIcon() override;
	Turret* createTurret() override;
	
};

