#pragma once

#include "Audio.h"
#include "Game.h"
class Game;

class Layer
{
public:
	Layer(Game* game);
	virtual void init() {};
	virtual void processControls() {};
	virtual void update() {};
	virtual void draw() {};

	/// <summary>
	/// Reproduce la música de fondo asociada a este Layer
	/// </summary>
	virtual void playMusic();

	Game* game;
	// Background music
	Mix_Music* backgroundMusic;
	bool toggleMusic;

};

