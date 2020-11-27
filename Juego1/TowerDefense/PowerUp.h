#pragma once
#include "Actor.h"
#include "Tower.h"

/// <summary>
/// Representa la clase base para los power-ups o mejoras
/// que irán apareciendo en el mapa, y que podrán ser recogidas
/// por el jugador para mejorar las torres.
/// </summary>
class PowerUp : public Actor
{
public:

	PowerUp(string filename, float width, float height, int ticksAlive, float x, float y, Game* game);

	/// <summary>
	/// Aplica el efecto del powerup sobre la torre
	/// pasada como parámetro.
	/// </summary>
	/// <param name="tower">Torre afectada por el powerup.</param>
	virtual void effect(Tower* tower) = 0;
	
	/// <summary>
	/// Método que devuelve un clone idéntico a este powerUp.
	/// </summary>
	/// <returns></returns>
	virtual PowerUp* clone() = 0;

	void update();


	bool collected; // Indica si el powerUp se ha recogido o no
	bool used; // Indica si el powerUp se ha usado o no
	int ticksAlive; // Ticks durante los que está vivo este powerUp

};

