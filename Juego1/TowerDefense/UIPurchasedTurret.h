#pragma once

#include "Actor.h"


/// <summary>
/// Clase que representa el icono de la interfaz de la
/// tienda que muestra la última torreta que se ha comprado o 
/// ninguna si no hay ninguna disponible para construir.
/// </summary>
class UIPurchasedTurret : public Actor
{
public:
	UIPurchasedTurret(float x, float y, Game* game);
	void draw() override;

	Actor* purchasedTurretIconView; // icono en miniatura con la torreta disponible.
};

