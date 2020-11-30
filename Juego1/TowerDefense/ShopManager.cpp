#include "ShopManager.h"

ShopManager::ShopManager(Player* player, Game* game) {
	this->player = player;
	this->game = game;
	this->purchasedTurret = nullptr;
	this->init();
}




void ShopManager::init() {
	UITurretItem * i1 = new UITurretItem("res/whiteSlot.png", new CannonFactory(game),
						WIDTH * 0.42, HEIGHT * 0.92, game);
	UITurretItem* i2 = new UITurretItem("res/whiteSlot.png", new MGFactory(game),
						WIDTH * 0.5, HEIGHT* 0.92, game);
	UITurretItem* i3 = new UITurretItem("res/whiteSlot.png", new MissileLauncherFactory(game),
						WIDTH * 0.58, HEIGHT * 0.92, game);
	this->turretItems.push_back(i1);
	this->turretItems.push_back(i2);
	this->turretItems.push_back(i3);
}


void ShopManager::draw() {
	for (auto const& item : turretItems) {
		item->draw();
	}
}

Turret* ShopManager::purchase(float x, float y) {
	UITurretItem* item = this->getClickedTurretItem(x, y);
	// Si se ha hecho click en un item de la tienda y además no hay ya una torreta comprada...
	if (item != nullptr && this->purchasedTurret == nullptr) {
		// Comprobar recursos del player
		int turretCost = item->turretFactory->getCost();
		TurretFactory* factory = item->turretFactory;
		if (player->availableResources >= turretCost) {
			this->purchasedTurret = factory->createTurret();
			this->purchasedTurret->x = x;
			this->purchasedTurret->y = y;
		}
	}
	return this->purchasedTurret;
}

void ShopManager::notifyTurretConstruction()
{
	this->player->availableResources -= this->purchasedTurret->cost;
	this->purchasedTurret = nullptr;
}

void ShopManager::clearPurchase()
{
	this->purchasedTurret = nullptr;
}

Turret* ShopManager::getPurchasedTurret()
{
	return this->purchasedTurret;
}

void ShopManager::updateTurretItems(int availableResources)
{
	for (auto const& slot : this->turretItems) {
		TurretFactory* factory = slot->turretFactory;
		if (availableResources >= factory->getCost()) { // Disponible
			slot->disable(false);
		}
		else { // No disponible
			slot->disable(true);
		}
	}
}


UITurretItem* ShopManager::getClickedTurretItem(float x, float y) {
	for (auto const& item : turretItems) {
		if (item->containsPoint(x, y)) {
			return item;
		}
	}
	return nullptr;
}