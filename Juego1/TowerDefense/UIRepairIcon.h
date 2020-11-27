#pragma once
#include "Actor.h"
#include "Text.h"

/// <summary>
///  Representa el icono de la UI que se mostrará
/// sobre los restos de una torreta para dar la capacidad de 
/// repararla
/// </summary>
class UIRepairIcon : public Actor
{
public:
	UIRepairIcon(float x, float y, int cost, Game* game);
	void draw() override;

	Text* txtCost;
};

