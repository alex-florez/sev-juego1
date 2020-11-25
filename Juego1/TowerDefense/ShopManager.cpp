#include "ShopManager.h"

ShopManager::ShopManager(Player* player, Game* game) {
	this->player = player;
	this->game = game;
	this->purchasedTurret = nullptr;
	this->init();
}




void ShopManager::init() {
	UITurretItem * i1 = new UITurretItem("res/itemSlot.png", new TurretAFactory(game),
						WIDTH * 0.45, HEIGHT * 0.92, game);
	UITurretItem* i2 = new UITurretItem("res/itemSlot.png", new TurretBFactory(game),
						WIDTH * 0.53, HEIGHT* 0.92, game);
	this->turretItems.push_back(i1);
	this->turretItems.push_back(i2);
	this->uiPurchasedTurret = new UIPurchasedTurret(0.3*WIDTH, 0.92 * HEIGHT, game);
}


void ShopManager::draw() {
	for (auto const& item : turretItems) {
		item->draw();
	}
	this->uiPurchasedTurret->draw();
}

void ShopManager::purchase(float x, float y) {
	UITurretItem* item = this->getClickedTurretItem(x, y);
	// Si se ha hecho click en un item de la tienda y además no hay ya una torreta comprada...
	if (item != nullptr && this->purchasedTurret == nullptr) {
		// Comprobar recursos del player
		int turretCost = item->turretFactory->getCost();
		TurretFactory* factory = item->turretFactory;
		if (player->availableResources >= turretCost) {
			player->availableResources -= turretCost;
			this->purchasedTurret = factory->createTurret();
			this->uiPurchasedTurret->purchasedTurretIconView = factory->getIcon();
		}
	}
}

void ShopManager::clearPurchase()
{
	this->purchasedTurret = nullptr;
	this->uiPurchasedTurret->purchasedTurretIconView = nullptr;
}

Turret* ShopManager::getPurchasedTurret()
{
	return this->purchasedTurret;
}


UITurretItem* ShopManager::getClickedTurretItem(float x, float y) {
	for (auto const& item : turretItems) {
		if (item->containsPoint(x, y)) {
			return item;
		}
	}
	return nullptr;
}