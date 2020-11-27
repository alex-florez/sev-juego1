#pragma once
#include "PowerUp.h"

/// <summary>
/// Representa una mejora que permite
/// reconstruir un torre.
/// </summary>
class ToolKit : public PowerUp
{
public:
	ToolKit(float x, float y, int aliveTicks, Game* game);
	void effect(Tower* tower) override;
	PowerUp* clone() override;
};

