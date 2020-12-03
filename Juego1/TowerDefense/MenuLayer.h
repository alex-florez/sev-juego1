#pragma once

#include "Layer.h"
#include "Actor.h"
#include "Background.h"
#include "SoundEffect.h"

class MenuLayer : public Layer
{
public:
	MenuLayer(Game* game);
	void init() override;
	void draw() override;
	void processControls() override;
	void keysToControls(SDL_Event event);
	void mouseToControls(SDL_Event event);


	// Controles del menú
	bool controlContinue;
	bool exit;

	Background* background;

	// Botones del menú
	Actor* buttonJugar; 
	Actor* buttonSalir;

	// Sonidos de los botones
	SoundEffect* jugarSound;
	SoundEffect* exitSound;
};

