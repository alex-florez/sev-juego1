#pragma once

#include <list>

#include "Game.h"
#include "Turret.h"
#include "ConstructionTile.h"
#include "ShopManager.h"

/// <summary>
/// Clase encargada de gestionar la compra y construcción
/// de torretas.
/// </summary>
class ConstructionManager
{
public:
	ConstructionManager(Game* game, ShopManager* shopManager);

	/// <summary>
	/// Recibe como parámetros las coordenadas en las que se ha
	/// hecho click y si hay algún construction tile en esas coordenadas
	/// construye la torreta pasada como parámetro. Si consigue construir
	/// la torreta con éxito se lo notifica al ShopManager
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <param name="turret">Referencia a objeto de tipo Turret</param>
	void construct(float x, float y, Turret* turret);


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
	Game* game;
	ShopManager* shopManager; // Referencia a la tienda

};

