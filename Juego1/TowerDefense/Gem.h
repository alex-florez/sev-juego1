#pragma once

#include "Actor.h"
#include "Animation.h"


/// <summary>
/// Clase que modela un coleccionable de recursos
/// para el jugador.
/// </summary>
class Gem : public Actor
{
public:
	Gem(string filename, int value, float width, float height, float x, float y, Game* game);
	void draw() override;

	int value;
	bool collected;
	Animation* glowAnimation; // Animación de brillo
};

