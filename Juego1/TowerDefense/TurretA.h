#pragma once

#include "Turret.h"
#include "Game.h"
#include "RoundProjectileFactory.h"

class TurretA : public Turret
{
public:
	TurretA(string filename, float x, float y, float width, float height, int cost, Game* game);

};

