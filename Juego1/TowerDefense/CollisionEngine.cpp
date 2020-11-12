#include "CollisionEngine.h"

CollisionEngine::CollisionEngine() {

}

void CollisionEngine::update() {

	// Colisiones entre enemigos y torres
	for (auto const& enemy : enemies) {
		for (auto const& pair : towers) {
			Tower* tower = pair.second;
			if (enemy->isOverlap(tower)) { // Enemigo colisiona con la torre
				enemy->attack(tower); // Hacer que ese enemigo ataque a esa torre.
			}
		}
	}
}