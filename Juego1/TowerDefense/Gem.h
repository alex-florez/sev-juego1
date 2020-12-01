#pragma once

#include "Actor.h"
#include "Animation.h"
#include "SoundEffect.h"


/// <summary>
/// Clase que modela un coleccionable de recursos
/// para el jugador.
/// </summary>
class Gem : public Actor
{
public:
	Gem(string filename, int value, int ticksAlive, float width, float height, float x, float y, Game* game);
	void draw() override;
	void update();

	int value;
	bool collected;
	bool blink; // Indica si se debe dibujar o no la gema
	int ticksAlive; // n� de ticks hasta que esta gema desaparezca.
	Animation* glowAnimation; // Animaci�n de brillo
	
	// Sonidos
	SoundEffect* pickUpSound;
};

