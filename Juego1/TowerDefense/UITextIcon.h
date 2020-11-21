#pragma once

#include "Actor.h"
#include "Text.h"


/// <summary>
/// Clase que representa el icono de la UI que muestra
/// un icono junto con un texto a la derecha.
/// </summary>
class UITextIcon : public Actor
{
public:
	UITextIcon(float x, float y, float width, float height, 
		string filename, string text, Game* game);
	void draw() override;
	Text* text;
};

