#pragma once

#include "Actor.h"
#include "Animation.h"
#include <math.h>

/// <summary>
/// Clase base para los distintos tipos de proyectiles.
/// </summary>
class Projectile : public Actor
{
public:
	Projectile(string filename, float width, float height, int speed, int damage, float x, float y, Game* game);
	void update();
	void draw() override;
	/// <summary>
	/// M�todo que calcula la velocidad vx y vy que es necesario
	/// aplicar al proyectil para que se dirija a las coordenadas
	/// pasadas como par�metro
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	void moveTo(float x, float y);


	int speed; // Velocidad del proyectil
	int damage; // Da�o causado por este proyectil
	bool impacted; // Indica si este proyectil ha impactado ya o no
	bool destroyed; // Indica si este proyectil est� destruido.
	Animation* impactAnimation; // Animaci�n ejecutada cuando impacta el proyectil.
};

