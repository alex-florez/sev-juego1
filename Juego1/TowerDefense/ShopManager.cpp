#include "ShopManager.h"

ShopManager::ShopManager(Player* player, Game* game) {
	this->player = player;
	this->game = game;
	this->init();
}


void ShopManager::init() {
	TurretItem* i1 = new TurretItem("res/turretAIcon.png", new TurretAFactory(game),
						WIDTH * 0.05, HEIGHT * 0.35, game);
	TurretItem* i2 = new TurretItem("res/turretBIcon.png", new TurretBFactory(game),
						WIDTH * 0.05, HEIGHT* 0.45, game);
	this->turretItems.push_back(i1);
	this->turretItems.push_back(i2);
}


void ShopManager::draw() {
	for (auto const& item : turretItems) {
		item->draw();
	}
}

Turret* ShopManager::purchase(float x, float y) {
	TurretItem* item = this->getClickedTurretItem(x, y);
	Turret* purchasedTurret = nullptr;
	// Comprobar el coste de la torreta y los recursos del player.
	if (item != nullptr) {
		purchasedTurret = item->turretFactory->createTurret();
	}
	return purchasedTurret;
}


TurretItem* ShopManager::getClickedTurretItem(float x, float y) {
	for (auto const& item : turretItems) {
		if (item->containsPoint(x, y)) {
			return item;
		}
	}
	return nullptr;
}