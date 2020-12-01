#pragma once
#include "Actor.h"
#include "Tower.h"
#include "SoundEffect.h"


/// <summary>
/// Representa la clase base para los power-ups o mejoras
/// que ir�n apareciendo en el mapa, y que podr�n ser recogidas
/// por el jugador para mejorar las torres.
/// </summary>
class PowerUp : public Actor
{
public:


	PowerUp(string filename, float width, float height, int ticksAlive, float x, float y, Game* game);

	/// <summary>
	/// Aplica el efecto del powerup sobre la torre
	/// pasada como par�metro. 
	/// </summary>
	/// <param name="tower">Torre afectada por el powerup.</param>
	virtual void effect(Tower* tower) = 0;
	
	/// <summary>
	/// M�todo que devuelve un clone id�ntico a este powerUp.
	/// </summary>
	/// <returns></returns>
	virtual PowerUp* clone() = 0;

	
	void draw() override;
	void update();

	
	bool collected; // Indica si el powerUp se ha recogido o no
	bool used; // Indica si el powerUp se ha usado o no
	bool blink; // Indica si el powerUp debe empezar a parpadear
	int ticksAlive; // Ticks durante los que est� vivo este powerUp
	Animation* glowAnimation; // Animaci�n de brillo

	// Sonidos
	SoundEffect* pickUpSound;
	SoundEffect* applySound;

};

