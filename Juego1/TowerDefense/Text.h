#pragma once

#include "Game.h"
#include "RGB.h"

class Text
{
public:
	Text(string content, float x, float y, RGB* rgb, Game* game);
	void draw();

	string content; // Texto
	int x;
	int y;
	int width;
	int height;
	RGB* rgb; // Color rgb
	Game* game; // Referencia al juego
};

