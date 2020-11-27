#include "UIRepairIcon.h"

UIRepairIcon::UIRepairIcon(float x, float y, int cost, Game* game)
	: Actor("res/repairIcon.png", x, y, 39, 40, game)
{
	this->txtCost = new Text(to_string(cost), x, y + 30, new RGB(0, 0, 0), game);
}

void UIRepairIcon::draw()
{
	Actor::draw();
	this->txtCost->draw();
}
