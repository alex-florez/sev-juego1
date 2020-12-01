#include "MG.h"


MG::MG(string filename, float x, float y, float width, float height, int cost, Game* game)
	: Turret(filename, x, y, width, height, cost, game) {

	this->projectileFactory = new MGBulletFactory(game);
	// Características de la torreta
	this->shootCadency = 5;
	this->xDetectionRange = 2;
	this->yDetectionRange = 2;

	this->shotSound = new SoundEffect("res/sounds/mg_sound2.wav");
}