#pragma once

#include "Player.h"
#include "Game.h"
#include "TurretItem.h"
#include "Turret.h"
#include "TurretAFactory.h"
#include "TurretBFactory.h"

/// <summary>
/// Clase que se encarga de toda la gestión de la compra
/// de torretas desde la interfaz de usuario.
/// </summary>
class ShopManager
{
public:
	ShopManager(Player* player, Game* game);

	/// <summary>
	/// Método encargado de dibujar sobre el render
	/// cada uno de los items de la UI que representan
	/// las torretas que se pueden comprar.
	/// </summary>
	void draw();

	/// <summary>
	/// Recibe como parámetros las coordenadas x e y en las que
	/// se ha hecho click, y si coinciden con uno de los items de la UI,
	/// y el jugador dispone de recursos suficientes, se crea una nueva torreta
	/// del tipo definido por ese item y se devuelve.
	/// </summary>
	/// <param name="x">Coordenada X</param>
	/// <param name="y">Coordenada Y</param>
	/// <returns>Objeto Turret del tipo concreto de la torreta representada por ese item</returns>
	Turret* purchase(float x, float y);

	Game* game;
	Player* player;
	list<TurretItem*> turretItems; // Lista con los items de la UI.

private:
	void init();
	TurretItem* getClickedTurretItem(float x, float y);
};

