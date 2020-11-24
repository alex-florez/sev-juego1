#pragma once

#include "Actor.h"
#include "Animation.h"
#include "Point.h"
#include "Path.h"
#include "Tower.h"
#include "Projectile.h"
#include "Pawn.h"
#include "Player.h"

#define ENEMY_SPEED 2

class Enemy : public Pawn
{
public:
	/// <summary>
	/// Enumerado que define los estados de un enemigo:
	///		* MOVING: se est� moviendo siguiendo la trayectoria que le corresponde.
	///		* ATTACKING: est� atacando a una de las torres.
	///		* DYING: ejecutando la animaci�n de muerte.
	///		* DEAD: animaci� de muerte terminada, enemigo muerto.
	/// </summary>
	enum class EnemyState { MOVING, ATTACKING, DYING, DEAD };

	Enemy(string filename, float width, float height, float x, float y, float speed, Game* game);
	void update();
	void draw() override;
	void impactedBy(Projectile* projectile, Player* player); // Enemigo recibe un impacto
	void attack(Tower* tower); // El enemigo ataca a una torre.

	Animation* aMoving; 
	Animation* aDying; 
	Animation* animation; // Referencia a la animaci�n actual.

	int attackFrequency; // Frecuencia de ataque del enemigo
	int ticksUntilNextAttack; // Ticks hasta efectuar el siguiente ataque.
	int health; // Variable que almacena la salud de este enemigo.

	EnemyState state; // Estado del enemigo.
};

