#include "MG.h"


MG::MG(string filename, float x, float y, float width, float height, int cost, Game* game)
	: Turret(filename, x, y, width, height, cost, game) {

	this->projectileFactory = new MGBulletFactory(game);
	// Caracter�sticas de la torreta
	this->shootCadency = 6;
	this->xDetectionRange = 2;
	this->yDetectionRange = 2;
	this->killedEnemiesForUpgrade = MG_KILLED_ENEMIES_FOR_UPGRADE;

	this->shotSound = new SoundEffect("res/sounds/mg_sound2.wav");

	// Offset cuando tiene un ca��n
	this->yCannonOffset = 5;

	// Valores "y" de los dos ca�ones
	this->upgradedYCannonOffsets[0] = -7;
	this->upgradedYCannonOffsets[1] = 7;

	this->upgradeCost = 350; // Coste de Upgrade
}

void MG::upgrade()
{
	this->updateTexture("res/turrets/mg/MGUpgraded.png");
	this->width = 44;
	this->height = 40;
	this->fileWidth = 44;
	this->fileHeight = 40;
	// Mejorar cadencia y �rea de efecto
	this->shootCadency -= 2;
	this->xDetectionRange += 2;
	this->yDetectionRange += 2;
	// Cambiar el estado
	this->state = TurretState::UPGRADED;
}

