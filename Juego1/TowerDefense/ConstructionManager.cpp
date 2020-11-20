#include "ConstructionManager.h"


ConstructionManager::ConstructionManager(Game* game) {
	this->currentTurret = nullptr;
	this->game = game;
}

void ConstructionManager::construct(float x, float y)
{
	// Comprobar que hay un construction tile en estas coordenadas
	ConstructionTile* ct = getClickedCT(x, y);
	if (ct != nullptr && !ct->occupied && this->currentTurret != nullptr) {
		float x = (int)(ct->x / TILE_WIDTH) * TILE_WIDTH + TILE_WIDTH / 2;
		float y = (int)(ct->y / TILE_HEIGHT) * TILE_HEIGHT + TILE_HEIGHT / 2;
		this->currentTurret->x = x;
		this->currentTurret->y = y;
		this->turrets.push_back(this->currentTurret);
		ct->occupied = true;
		this->currentTurret = nullptr;
	}
}


void ConstructionManager::construct(ConstructionTile* ct) {
	if (!ct->occupied) {
		float x = (int)(ct->x / TILE_WIDTH) * TILE_WIDTH + TILE_WIDTH / 2;
		float y = (int)(ct->y / TILE_HEIGHT) * TILE_HEIGHT + TILE_HEIGHT / 2;
		Turret* newTurret = new Turret("res/cannon1.png", x, y, 55, 14, game);
		// Colocar la torreta de currentTurret
		this->turrets.push_back(newTurret);
		ct->occupied = true;
	}
}


ConstructionTile* ConstructionManager::getClickedCT(float x, float y) {
	for (auto const& ct : constructionTiles) {
		if (ct->containsPoint(x, y)) {
			return ct;
		}
	}
	return nullptr;
}


void ConstructionManager::addConstructionTile(ConstructionTile* ct) {
	this->constructionTiles.push_back(ct);
}