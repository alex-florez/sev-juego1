#pragma once

#include "Actor.h"
#include "Text.h"

/// <summary>
/// Elemento de la UI que representa un contador que indica
/// el nº de Horda actual.
/// </summary>
class UIHordeCounter : public Actor
{
public:
	UIHordeCounter(float x, float y, Game* game);
	void draw() override;

	Text* hordeNumberTxt; // Texto del nº de horda
	Text* label; // Etiqueta "Horda"

};

