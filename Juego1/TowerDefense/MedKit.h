#pragma once
#include "PowerUp.h"

/// <summary>
/// Representa un powerup de un botiquín,
/// que incrementa la salud de la torre sobre la que se aplica
/// </summary>
class MedKit : public PowerUp
{
public:

	MedKit(float x, float y, int aliveTicks, Game* game);


	void effect(Tower* tower) override;
	PowerUp* clone() override;
};

