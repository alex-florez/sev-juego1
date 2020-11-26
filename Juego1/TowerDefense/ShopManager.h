#pragma once

#include "Player.h"
#include "Game.h"
#include "UITurretItem.h"
#include "Turret.h"
#include "TurretAFactory.h"
#include "TurretBFactory.h"
#include "Turret.h"
#include "UIPurchasedTurret.h"

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
	/// las torretas que se pueden comprar, así como el slot en 
	/// el que se muestra la torreta disponible para ser construida.
	/// </summary>
	void draw();

	/// <summary>
	/// Recibe como parámetros las coordenadas x e y en las que
	/// se ha hecho click, y si coinciden con uno de los items de la UI,
	/// y el jugador dispone de recursos suficientes, se crea una nueva torreta
	/// del tipo definido por ese item y se retorna. En caso contrario devuelve nullptr
	/// </summary>
	/// <param name="x">Coordenada X</param>
	/// <param name="y">Coordenada Y</param>
	Turret* purchase(float x, float y);

	/// <summary>
	/// Será invocado por el ConstructionManager una vez la torreta se haya
	/// colocado con éxito.
	/// </summary>
	void notifyTurretConstruction();

	/// <summary>
	/// Se encarga de limpiar la compra, es decir, establecer a nullptr
	/// la torreta comprada.
	/// </summary>
	void clearPurchase();

	/// <summary>
	/// Devuelve una referencia a la torreta que se acaba de
	/// comprar en la tienda.
	/// </summary>
	/// <returns></returns>
	Turret* getPurchasedTurret();

	Game* game;
	Player* player;
	list<UITurretItem*> turretItems; // Lista con los items de la UI.
	Turret* purchasedTurret; // Almacena una referencia a una torreta que se ha comprado.
	UIPurchasedTurret* uiPurchasedTurret; // Icono de la interfaz que muestra la torreta recién comprada disponible.

private:
	void init();
	UITurretItem* getClickedTurretItem(float x, float y);
	
};

