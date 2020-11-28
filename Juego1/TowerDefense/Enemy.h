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
	///		* MOVING: se está moviendo siguiendo la trayectoria que le corresponde.
	///		* ATTACKING: está atacando a una de las torres.
	///		* DYING: ejecutando la animación de muerte.
	///		* DEAD: animació de muerte terminada, enemigo muerto.
	/// </summary>
	enum class EnemyState { MOVING, ATTACKING, DYING, DEAD };

	/// <summary>
	/// Enumerado con las posibles orientacioenes del actor
	/// </summary>
	enum class Orientation {LEFT, RIGHT, TOP, BOTTOM};

	Enemy(string filename, float width, float height, float x, float y, float speed, Game* game);
	void update();
	void draw() override;
	void impactedBy(Projectile* projectile, Player* player); // Enemigo recibe un impacto
	void attack(Tower* tower); // El enemigo ataca a una torre.

	// Animaciones

	Animation* aMovingLeft;
	Animation* aMovingRight;

	Animation* aDyingLeft;
	Animation* aDyingRight;

	Animation* aHurtRight;
	Animation* aHurtLeft;

	Animation* aAttackingLeft;
	Animation* aAttackingRight;


	Animation* animation; // Referencia a la animación actual.
	Orientation orientation; // Orientación actual.

	int attackFrequency; // Frecuencia de ataque del enemigo
	int attackPower; // Poder de ataque
	int ticksUntilNextAttack; // Ticks hasta efectuar el siguiente ataque.
	int health; // Variable que almacena la salud de este enemigo.
	bool hit; // Indica si ha recibido un impacto


	EnemyState state; // Estado del enemigo.
};

