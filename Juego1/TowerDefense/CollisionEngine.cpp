#include "CollisionEngine.h"

CollisionEngine::CollisionEngine() {

}


void CollisionEngine::addTowers(map<int, Tower*>* towers) {
	this->towers = towers;
}

void CollisionEngine::addEnemies(list<Enemy*>* enemies) {
	this->enemies = enemies;
}

void CollisionEngine::addProjectiles(list<Projectile*>* projectiles) {
	this->projectiles = projectiles;
}

void CollisionEngine::addPlayer(Player* player) {
	this->player = player;
}


void CollisionEngine::update() {

	// Colisiones entre enemigos y proyectiles
	for (auto const& enemy : *enemies) {
		for (auto const& projectile : *projectiles) {
			if (enemy->isOverlap(projectile)
				&& !projectile->impacted) { // Si el proyectil ya había impactado, entonces ya no debe tener efecto sobre el enemigo
				enemy->impactedBy(projectile, player);
				projectile->impacted = true;
			}
		}
	}

	// Colisiones entre enemigos y torres
	for (auto const& enemy : *enemies) {
		if(enemy->state != Enemy::EnemyState::DYING && enemy->state != Enemy::EnemyState::DEAD)
			enemy->state = Enemy::EnemyState::MOVING;
		for (auto const& pair : *towers) {
			Tower* tower = pair.second;
			if (enemy->isOverlap(tower) && tower->state == Tower::TowerState::ALIVE) { // Enemigo colisiona con la torre que está viva
				enemy->attack(tower); // Hacer que ese enemigo ataque a esa torre.
			}
		}
	}
}