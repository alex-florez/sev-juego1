#include "MG.h"


MG::MG(string filename, float x, float y, float width, float height, int cost, Game* game)
	: Turret(filename, x, y, width, height, cost, game) {

	this->projectileFactory = new MGBulletFactory(game);
	// Características de la torreta
	this->shootCadency = 7;
	this->xDetectionRange = 3;
	this->yDetectionRange = 3;
	this->killedEnemiesForUpgrade = MG_KILLED_ENEMIES_FOR_UPGRADE;

	this->shotSound = new SoundEffect("res/sounds/mg_sound2.wav");

	// Offset cuando tiene un cañón
	this->yCannonOffset = 5;

	// Valores "y" de los dos cañones
	this->upgradedYCannonOffsets[0] = -7;
	this->upgradedYCannonOffsets[1] = 7;

	this->upgradeCost = 300; // Coste de Upgrade
}

void MG::upgrade()
{
	this->updateTexture("res/turrets/mg/MGUpgraded.png");
	this->width = 44;
	this->height = 40;
	this->fileWidth = 44;
	this->fileHeight = 40;
	// Cambiar el estado
	this->state = TurretState::UPGRADED;
}

