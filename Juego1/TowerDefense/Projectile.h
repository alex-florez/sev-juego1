#pragma once

#include "Actor.h"
#include "Animation.h"
#include "SoundEffect.h"

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
	/// Método que calcula la velocidad vx y vy que es necesario
	/// aplicar al proyectil para que se dirija a las coordenadas
	/// pasadas como parámetro
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	void moveTo(float x, float y);


	/// <summary>
	/// Actualiza el ángulo del proyectil y también de sus animaciones
	/// que lo necesiten.
	/// </summary>
	/// <param name="angle"></param>
	virtual void updateAngle(float angle);

	/// <summary>
	/// Método invocado cuando el proyectil impacta contra
	/// un enemigo.
	/// </summary>
	void impact();

	int speed; // Velocidad del proyectil
	int damage; // Daño causado por este proyectil
	bool impacted; // Indica si este proyectil ha impactado ya o no
	bool destroyed; // Indica si este proyectil está destruido.
	Animation* impactAnimation; // Animación ejecutada cuando impacta el proyectil.
	int turretId; // Id que hace referencia a la torreta que disparó este proyectil.

	// Sonidos
	SoundEffect* hitSound;
};

