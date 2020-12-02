#pragma once

#include "Actor.h"
#include "TurretFactory.h"
#include "Text.h"
#include "SoundEffect.h"

/// <summary>
/// Clase que modela un icono de la interfaz de usuario
/// para comprar una torreta de un tipo específico.
/// </summary>
class UITurretItem : public Actor
{
public:
	UITurretItem(string filename, TurretFactory* turretFactory, float x, float y, Game* game);
	void draw() override;
	/// <summary>
	/// Cambia el slot para que pase a ser de color rojo
	/// indicando que no hay suficientes recursos para comprar esa torreta.
	/// </summary>
	void disable(bool enabled);

	TurretFactory* turretFactory;
	Actor* turretIcon; // Icono que representa a este tipo de torreta.
	Text* txtCost; // Elemento de texto que muesta el coste de este tipo de torretas.

	// Sonidos
	SoundEffect* validSound;
	SoundEffect* wrongSound;
	SoundEffect* clickSound;
};

