#include "TurretAFactory.h"


TurretAFactory::TurretAFactory(Game* game)
	: TurretFactory(game) {
	// Crear el icono en miniatura
	this->iconView = new Actor("res/cannon1Icon.png", 0, 0, 43, 11, game);
	this->iconName = "res/cannon1Icon.png";
	this->iconWidth = 43;
	this->iconHeight = 11;
	this->cost = 200;
}

Turret* TurretAFactory::createTurret() {
	return new TurretA("res/cannon1.png", 0, 0, 55, 14, game);
}