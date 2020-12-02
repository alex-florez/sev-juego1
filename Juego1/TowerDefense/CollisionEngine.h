#pragma once

#include <map>
#include <list>

#include "Tower.h"
#include "Enemy.h"
#include "Player.h"
#include "Turret.h"

/// <summary>
/// Clase que modela un motor muy simple de colisiones.
/// </summary>
class CollisionEngine
{
public:
	CollisionEngine();
	void update();
	void addTowers(map<int, Tower*>* towers);
	void addEnemies(list<Enemy*>* enemies);
	void addProjectiles(list<Projectile*>* projectiles);
	void addPlayer(Player* player);
	void addTurrets(list<Turret*>* turrets);

	/// <summary>
	/// Puntero al mapa de torres que hay en el render.
	/// </summary>
	map<int, Tower*>* towers;

	/// <summary>
	/// Puntero a la lista de enemigos en el render.
	/// </summary>
	list<Enemy*>* enemies;

	/// <summary>
	/// Puntero a la lista de proyectiles en el render.
	/// </summary>
	list<Projectile*>* projectiles;

	/// <summary>
	/// Referencia al jugador.
	/// </summary>
	Player* player;

	/// <summary>
	/// Puntero a la lista de torretas almacenada en el 
	/// construction Manager
	/// </summary>
	list<Turret*>* turrets;

private:
	/// <summary>
	/// Devuelve una referencia a la torreta cuyo id
	/// coincide con el pasado como parámetro.
	/// </summary>
	/// <param name="id"></param>
	/// <returns></returns>
	Turret* getTurretById(int id);
};

