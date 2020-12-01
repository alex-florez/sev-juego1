#include "Missile.h"

Missile::Missile(float x, float y, Game* game)
	: Projectile("res/turrets/missileLauncher/Missile.png", 23, 13, 13, 55, x, y, game)
{
	this->flames = new Animation("res/rocket_effect.png", 50, 50, 500, 50, 1, 10, true, game);
	this->hitSound = new SoundEffect("res/sounds/missile_explosion.wav");
}

void Missile::draw()
{
	//if (!impacted) {
	//	this->flames->update();
	//	// Calcular coordenadas
	//	float senx = sin(this->angle);
	//	float cosx = cos(this->angle);
	//	float tailX = cosx * (this->width / 2);
	//	float tailY = senx * (this->width / 2);
	//	this->flames->draw(x - tailX, y - tailY);
	//}

	Projectile::draw();
}
void Missile::updateAngle(float angle)
{
	this->angle = angle;
	this->flames->angle = angle;
}

