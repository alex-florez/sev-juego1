#pragma once

#include <SDL.h>
#include <SDL_mixer.h>

#include <iostream>
#include <string>

using namespace std;

/// <summary>
/// Clase que representa un efecto de sonido
/// </summary>
class SoundEffect
{
public:
	SoundEffect(string filename);
	~SoundEffect();
	void play();
	void free();

	Mix_Chunk* chunk;
};

