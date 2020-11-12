#include "CollisionEngine.h"

CollisionEngine::CollisionEngine() {

}

void CollisionEngine::update() {

	// Colisiones entre enemigos y torres
	for (auto const& enemy : enemies) {
		enemy->isCollisioning = false;
		for (auto const& pair : towers) {
			Tower* tower = pair.second;
			if (enemy->isOverlap(tower) && !tower->invisible) { // Enemigo colisiona con la torre si esta no se está destruyendo...
				enemy->isCollisioning = true;
				enemy->attack(tower); // Hacer que ese enemigo ataque a esa torre.
			}
		}
	}
}