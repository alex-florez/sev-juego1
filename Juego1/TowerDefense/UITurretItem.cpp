#include "UITurretItem.h"


UITurretItem::UITurretItem(string filename, TurretFactory* turretFactory, float x, float y, Game* game)
	: Actor(filename, x, y, 50, 50, game) {

	this->turretFactory = turretFactory;
	this->turretIcon = new Actor(this->turretFactory->iconName, x, y, 
	this->turretFactory->iconWidth, this->turretFactory->iconHeight, game);
	this->txtCost = new Text(to_string(this->turretFactory->cost), 
		x, y + this->height / 2 + 10, new RGB(0,0,0), game);
}


void UITurretItem::draw(){
	Actor::draw();
	this->turretIcon->draw();
	this->txtCost->draw();
}