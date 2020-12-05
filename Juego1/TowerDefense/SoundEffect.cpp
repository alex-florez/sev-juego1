#include "SoundEffect.h"

SoundEffect::SoundEffect(string filename)
{
	this->chunk = Mix_LoadWAV(filename.c_str());
	Mix_Volume(-1, 30); // Volumen de los efectos
}

void SoundEffect::play()
{
	Mix_PlayChannel(-1, this->chunk, 0);
}

SoundEffect::~SoundEffect() {
	Mix_FreeChunk(this->chunk);
}

void SoundEffect::free() {
	Mix_FreeChunk(this->chunk);
}