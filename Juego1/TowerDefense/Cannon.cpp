#include "Cannon.h"


Cannon::Cannon(string filename, float x, float y, float width, float height, int cost, Game* game)
	: Turret(filename, x, y, width, height, cost, game) {

	this->projectileFactory = new BulletProjectileFactory(game);
	// Características de la torreta
	this->shootCadency = 30;
	this->xDetectionRange = 4;
	this->yDetectionRange = 4;
	this->killedEnemiesForUpgrade = CANNON_KILLED_ENEMIES_FOR_UPGRADE;

	this->shotSound = new SoundEffect("res/sounds/cannon_sound.wav");
	
	// Offset cuando tiene un cañón
	this->yCannonOffset = 0;

	// Valores "y" de los dos cañones
	this->upgradedYCannonOffsets[0] = -10;
	this->upgradedYCannonOffsets[1] = 10;

	this->upgradeCost = 200; // Coste de Upgrade
}

void Cannon::upgrade()
{
	this->updateTexture("res/turrets/cannon/CannonUpgraded.png");
	this->width = 44;
	this->height = 31;
	this->fileWidth = 44;
	this->fileHeight = 31;
	// Cambiar el estado
	this->state = TurretState::UPGRADED;
}
