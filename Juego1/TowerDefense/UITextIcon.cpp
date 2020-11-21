#include "UITextIcon.h"

UITextIcon::UITextIcon(float x, float y, float width, float height,
	string filename, string text, Game* game)
	: Actor(filename, x, y, width, height, game) {

	this->text = new Text(text, x + 42, y, game);
}

void UITextIcon::draw() {
	Actor::draw();
	this->text->draw();
}