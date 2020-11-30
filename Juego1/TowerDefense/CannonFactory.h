#pragma once

#include "TurretFactory.h"
#include "Cannon.h"



class CannonFactory : public TurretFactory
{
public:
	CannonFactory(Game* game);

	int getCost() override;
	Actor* getIcon() override;
	Turret* createTurret() override;
	
};

