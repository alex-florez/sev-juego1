#include "UIPurchasedTurret.h"

UIPurchasedTurret::UIPurchasedTurret(float x, float y, Game* game)
	: Actor("res/slot.png", x, y, 50, 50, game) {

	this->purchasedTurretIconView = nullptr;
}


void UIPurchasedTurret::draw() {
	Actor::draw();
	if (this->purchasedTurretIconView != nullptr) {
		this->purchasedTurretIconView->x = this->x;
		this->purchasedTurretIconView->y = this->y;
		this->purchasedTurretIconView->draw();
	}
}