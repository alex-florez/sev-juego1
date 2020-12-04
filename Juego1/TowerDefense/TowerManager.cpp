#include "TowerManager.h"

TowerManager::TowerManager(Game* game)
{
	this->game = game;
	this->explosionSound = new SoundEffect("res/sounds/tower_explosion.wav");
}

void TowerManager::draw()
{
	for (auto const& pair : towers) {
		pair.second->draw();
	}
}

Tower* TowerManager::getTower(float x, float y)
{
	for (auto const& pair : towers) {
		if (pair.second->containsPoint(x, y))
			return pair.second;
	}
	return nullptr;
}

void TowerManager::add(int key, Tower* tower)
{
	tower->explosionSound = this->explosionSound;
	this->towers[key] = tower;
}

void TowerManager::remove(int key)
{
	this->towers.erase(key);
}

bool TowerManager::allDestroyed()
{
	bool destroyed = true;
	for (auto const& pair : this->towers) {
		if (pair.second->state != Tower::TowerState::DESTROYED) {
			destroyed = false;
			break;
		}
	}
	return destroyed;
}
