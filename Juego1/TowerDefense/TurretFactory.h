#pragma once

#include "Turret.h"

/// <summary>
/// Clase base abstracta para implementar un patrón
/// FactoryMethod. Representa una factoría de torretas.
/// </summary>
class TurretFactory
{
public:
	TurretFactory(Game* game);

	virtual Turret* createTurret() = 0;

	Game* game;
	Actor* iconView; // Representa un icono con la miniatura de la torreta.
	string iconName; // String que almacena el nombre del fichero con el icono de la torreta.
	float iconWidth; // Ancho del icono
	float iconHeight; // Alto del icono
	int cost; // Coste de las torretas del tipo que crea este factory
};

