#pragma once

#include "Actor.h"
#include "TurretFactory.h"

/// <summary>
/// Clase que modela un icono de la interfaz de usuario
/// para comprar una torreta de un tipo específico.
/// </summary>
class TurretItem : public Actor
{
public:
	TurretItem(string filename, TurretFactory* turretFactory, float x, float y, Game* game);

	TurretFactory* turretFactory;
};

