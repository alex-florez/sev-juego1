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
/// Clase que se encarga de toda la gesti�n de la compra
/// de torretas desde la interfaz de usuario.
/// </summary>
class ShopManager
{
public:
	ShopManager(Player* player, Game* game);

	/// <summary>
	/// M�todo encargado de dibujar sobre el render
	/// cada uno de los items de la UI que representan
	/// las torretas que se pueden comprar, as� como el slot en 
	/// el que se muestra la torreta disponible para ser construida.
	/// </summary>
	void draw();

	/// <summary>
	/// Recibe como par�metros las coordenadas x e y en las que
	/// se ha hecho click, y si coinciden con uno de los items de la UI,
	/// y el jugador dispone de recursos suficientes, se crea una nueva torreta
	/// del tipo definido por ese item.
	/// </summary>
	/// <param name="x">Coordenada X</param>
	/// <param name="y">Coordenada Y</param>
	void purchase(float x, float y);

	/// <summary>
	/// Establece como torreta comprada la referencia
	/// pasada como par�metro.
	/// </summary>
	/// <param name="turret">Referencia a objeto de tipo Turret</param>
	void setPurchasedTurret(Turret* turret);

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
	UIPurchasedTurret* uiPurchasedTurret; // Icono de la interfaz que muestra la torreta reci�n comprada disponible.

private:
	void init();
	UITurretItem* getClickedTurretItem(float x, float y);
	
};

