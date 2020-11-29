#include "UITurretItem.h"


UITurretItem::UITurretItem(string filename, TurretFactory* turretFactory, float x, float y, Game* game)
	: Actor(filename, x, y, 50, 54, game) {

	this->turretFactory = turretFactory;
	this->turretIcon = turretFactory->getIcon();
	this->turretIcon->x = x;
	this->turretIcon->y = y;
	this->txtCost = new Text(to_string(this->turretFactory->getCost()), 
		x, y + this->height / 2 + 10, new RGB(0,0,0), game);
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
	}
	else {
		this->updateTexture("res/whiteSlot.png");
	}
}
