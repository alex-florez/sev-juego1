#include "UITurretItem.h"


UITurretItem::UITurretItem(string filename, TurretFactory* turretFactory, float x, float y, Game* game)
	: Actor(filename, x, y, 50, 54, game) {

	this->turretFactory = turretFactory;
	this->turretIcon = turretFactory->getIcon();
	this->turretIcon->x = x;
	this->turretIcon->y = y;
	this->txtCost = new Text(to_string(this->turretFactory->getCost()), 
		x, y + this->height / 2 + 10, new RGB(0,0,0), game);

	this->validSound = new SoundEffect("res/sounds/uiPickTurret.wav");
	this->wrongSound = new SoundEffect("res/sounds/wrong.wav");
	this->clickSound = validSound;
}


void UITurretItem::draw(){
	Actor::draw();
	this->turretIcon->draw();
	this->txtCost->draw();
}

void UITurretItem::disable(bool disable)
{
	if (disable) {
		this->updateTexture("res/redSlot.png");
		this->clickSound = wrongSound;
	}
	else {
		this->updateTexture("res/whiteSlot.png");
		this->clickSound = validSound;
	}
}
