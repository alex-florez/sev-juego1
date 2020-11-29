#include "UIHordeCounter.h"

UIHordeCounter::UIHordeCounter(float x, float y, Game* game)
	: Actor("", x, y, 0, 0, game)
{

	this->label = new Text("Horda", x-20, y, new RGB(179, 14, 37), game);
	this->hordeNumberTxt = new Text("1", x - 20 + this->label->width + 60, y, new RGB(255, 237, 0), game);
}

void UIHordeCounter::draw()
{
	this->label->draw();
	this->hordeNumberTxt->draw();
 

}
