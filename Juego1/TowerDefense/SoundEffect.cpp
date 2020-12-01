#include "SoundEffect.h"

SoundEffect::SoundEffect(string filename)
{
	//if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096)) {
	//	cout << "Error: " << Mix_GetError() << endl;
	//}
	this->chunk = Mix_LoadWAV(filename.c_str());
}

void SoundEffect::play()
{
	Mix_PlayChannel(-1, this->chunk, 0);
}

SoundEffect::~SoundEffect() {
	Mix_FreeChunk(this->chunk);
}
