#include "MissileLauncher.h"

MissileLauncher::MissileLauncher(string filename, float x, float y, float width, float height, int cost, Game* game)
	: Turret(filename, x, y, width, height, cost, game)
{
	this->projectileFactory = new MissileFactory(game);
	// Características de la torreta
	this->shootCadency = 60;
	this->xDetectionRange = 6;
	this->yDetectionRange = 6;
	this->killedEnemiesForUpgrade = MISSILE_LAUNCHER_KILLED_ENEMIES_FOR_UPGRADE;

	this->shotSound = new SoundEffect("res/sounds/missile_launch.wav");
	// Offset cuando tiene un cañón
	this->yCannonOffset = 0;

	// Valores "y" de los dos cañones
	this->upgradedYCannonOffsets[0] = -10;
	this->upgradedYCannonOffsets[1] = 10;

	this->upgradeCost = 500; // Coste de Upgrade
}

void MissileLauncher::upgrade()
{
	this->updateTexture("res/turrets/missileLauncher/MissileLauncherUpgraded.png");
	this->width = 44;
	this->height = 44;
	this->fileWidth = 44;
	this->fileHeight = 44;
	// Cambiar el estado
	this->state = TurretState::UPGRADED;
}
