#include "ConstructionManager.h"


ConstructionManager::ConstructionManager(Game* game, ShopManager* shopManager) {
	this->game = game;
	this->shopManager = shopManager;
	this->constructionSound = new SoundEffect("res/sounds/purchase.wav");
	this->numberOfTotalTurrets = 0;
}

void ConstructionManager::construct(float x, float y, Turret* turret)
{
	// Comprobar que hay un construction tile en estas coordenadas
	ConstructionTile* ct = getClickedCT(x, y);
	if (ct != nullptr && !ct->occupied && turret != nullptr) {
		float x = (int)(ct->x / TILE_WIDTH) * TILE_WIDTH + TILE_WIDTH / 2;
		float y = (int)(ct->y / TILE_HEIGHT) * TILE_HEIGHT + TILE_HEIGHT / 2;
		// Coordenadas de la torreta
		turret->x = x;
		turret->y = y;
		turret->state = Turret::TurretState::BUILDING; // Cambiar el estado de la torreta a en construcción
		turret->id = this->numberOfTotalTurrets++; // Id de la torreta.
		this->turrets.push_back(turret);
		ct->occupied = true;
		this->constructionSound->play(); // Reproducir sonido
		// Notificar al Shop manager de que la torreta comprada ya ha sido colocada.
		this->shopManager->notifyTurretConstruction();
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