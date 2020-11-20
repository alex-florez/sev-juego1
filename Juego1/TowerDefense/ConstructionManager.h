#pragma once

#include <list>

#include "Game.h"
#include "Player.h"
#include "Turret.h"
#include "ConstructionTile.h"

/// <summary>
/// Clase encargada de gestionar la compra y construcción
/// de torretas.
/// </summary>
class ConstructionManager
{
public:
	ConstructionManager(Game* game);

	void construct(float x, float y);

	/// <summary>
	/// Construye una torreta sobre el constructionTile
	/// pasado como parámetro, siempre y cuando este no esté
	/// ocupado y haya alguna torreta seleccionada para construir.
	/// </summary>
	void construct(ConstructionTile* ct);

	/// <summary>
	/// Dadas unas coordenadas x e y, recorre la lista de tiles 
	/// construibles y devuelve aquel sobre el cual se ha hecho
	/// click.
	/// </summary>
	/// <param name="x">Click x</param>
	/// <param name="y">Click y</param>
	/// <returns></returns>
	ConstructionTile* getClickedCT(float x, float y);

	/// <summary>
	/// Añade un nuevo tile donde se puede construir a la lista
	/// de ConstructionTiles.
	/// </summary>
	/// <param name="ct">Nuevo ConstructionTile</param>
	void addConstructionTile(ConstructionTile* ct);
	
	list<ConstructionTile*> constructionTiles; // Lista de tiles en los que se puede construir.
	list<Turret*> turrets; // Torretas construidas hasta ahora.
	Turret* currentTurret; // Referencia a la torreta que se ha adquirido
	Player* player;
	Game* game;

};

