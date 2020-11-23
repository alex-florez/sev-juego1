#include "Text.h"

Text::Text(string content, float x, float y, RGB* rgb, Game* game) {
	this->content = content;
	this->x = x;
	this->y = y;
	if (rgb == nullptr)
		this->rgb = new RGB(0, 0, 0);
	else this->rgb = rgb;
	this->game = game;
}


void Text::draw() {
	SDL_Color color;
	color.r = this->rgb->r;
	color.g = this->rgb->g;
	color.b = this->rgb->b;
	color.a = 255; // Transparencia: 255 -> Opaco

	SDL_Surface* surface = TTF_RenderText_Blended(game->font, content.c_str(), color);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(game->renderer, surface);

	SDL_Rect rect; // Base de coordenadas esquina superior izquierda
	rect.x = x - surface->w / 2;
	rect.y = y - surface->h / 2;
	rect.w = surface->w;
	rect.h = surface->h;

	SDL_FreeSurface(surface);
	SDL_RenderCopy(game->renderer, texture, NULL, &rect);
	SDL_DestroyTexture(texture);
}