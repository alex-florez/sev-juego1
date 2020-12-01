#include "MissileLauncher.h"

MissileLauncher::MissileLauncher(string filename, float x, float y, float width, float height, int cost, Game* game)
	: Turret(filename, x, y, width, height, cost, game)
{
	this->projectileFactory = new MissileFactory(game);
	// CaracterÝsticas de la torreta
	this->shootCadency = 60;
	this->xDetectionRange = 6;
	this->yDetectionRange = 6;

	this->shotSound = new SoundEffect("res/sounds/missile_launch.wav");
}
