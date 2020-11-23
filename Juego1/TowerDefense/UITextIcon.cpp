#include "UITextIcon.h"

UITextIcon::UITextIcon(float x, float y, float width, float height,
	float padding, RGB* rgb, string filename, string text, Game* game)
	: Actor(filename, x, y, width, height, game) {

	this->text = new Text(text, x + padding, y, rgb, game);
}

void UITextIcon::draw() {
	Actor::draw();
	this->text->draw();
}