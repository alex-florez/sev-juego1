#include "Layer.h"

Layer::Layer(Game* game) {
	this->game = game;
	// Sonido
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096)) {
		cout << "Error: " << Mix_GetError() << endl;
	}
	this->toggleMusic = false;
}

void Layer::playMusic()
{
	Mix_PlayMusic(backgroundMusic, -1);
}
