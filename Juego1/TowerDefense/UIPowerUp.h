#pragma once

#include "Actor.h"
#include "PowerUp.h"
#include "SoundEffect.h"

/// <summary>
/// Clase que representa el slot de la UI que almacena
/// un powerUp recogido por el usuario
/// </summary>
class UIPowerUp : public Actor
{
public:
	UIPowerUp(float x, float y, Game* game);
	void draw() override;
	bool empty();
	void clear();
	void setPowerUp(PowerUp* powerUp);


	PowerUp* powerUp; // Referencia al powerUp almacenado en este slot.

	// Sonidos
	SoundEffect* clickSound;

};

