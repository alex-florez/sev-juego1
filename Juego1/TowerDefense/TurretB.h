#pragma once

#include "Turret.h"
#include "Game.h"


class TurretB : public Turret
{
public:
	TurretB(string filename, float x, float y, float width, float height, int cost, Game* game);
};

