#pragma once

#include "Actor.h"
#include "TurretFactory.h"
#include "Text.h"

/// <summary>
/// Clase que modela un icono de la interfaz de usuario
/// para comprar una torreta de un tipo específico.
/// </summary>
class UITurretItem : public Actor
{
public:
	UITurretItem(string filename, TurretFactory* turretFactory, float x, float y, Game* game);
	void draw() override;

	TurretFactory* turretFactory;
	Actor* turretIcon; // Icono que representa a este tipo de torreta.
	Text* txtCost; // Elemento de texto que muesta el coste de este tipo de torretas.
};

