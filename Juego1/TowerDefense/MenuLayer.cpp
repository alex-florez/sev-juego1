#include "MenuLayer.h"


MenuLayer::MenuLayer(Game* game)
	: Layer(game) {

	init();
	backgroundMusic = Mix_LoadMUS("res/sounds/menuSynthwave.mp3");
	this->playMusic();
}

void MenuLayer::init() {
	// Sonido
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096)) {
		cout << "Error: " << Mix_GetError() << endl;
	}
	// Volumen
	Mix_VolumeMusic(10);

	// Fondo normal sin velocidad
	background = new Background("res/TowerDefenseMenu.png", WIDTH * 0.5, HEIGHT * 0.5, game);
	buttonJugar = new Actor("res/BotonJugar.png", WIDTH * 0.49, HEIGHT * 0.38, 150, 63, game);
	buttonSalir = new Actor("res/BotonSalir.png", WIDTH * 0.49, HEIGHT * 0.50, 149, 62, game);
	exit = false;
	controlContinue = false;

	// instanciar sonidos
	this->jugarSound = new SoundEffect("res/sounds/menuJugarSound.wav");
	this->exitSound = new SoundEffect("res/sounds/menuSalirSound.wav");

}

void MenuLayer::draw() {
	background->draw();
	buttonJugar->draw();
	buttonSalir->draw();

	SDL_RenderPresent(game->renderer);
}

void MenuLayer::processControls() {
	// obtener controles
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		// Seleccionar tipo de entrada
		if (event.type == SDL_QUIT)
			this->exit = true;

		if (event.type == SDL_KEYDOWN) {
			game->input = GameInputType::KEYBOARD;
		}
		if (event.type == SDL_MOUSEBUTTONDOWN) {
			game->input = GameInputType::MOUSE;
		}

		// Procesar teclas
		if (game->input == GameInputType::KEYBOARD) {
			keysToControls(event);
		}
		if (game->input == GameInputType::MOUSE) {
			mouseToControls(event);
		}

		// Procesar controles
		// Jugar
		if (controlContinue) {
			// Cambiar la capa
			game->layer = game->gameLayer;
			Mix_HaltMusic();
			game->layer->playMusic();
			controlContinue = false;
		}

		// Salir del juego
		if (exit) {
			game->loopActive = false;
		}

		// Controles de música
		if (toggleMusic) {
			if (Mix_PausedMusic()) {
				Mix_ResumeMusic();
			}
			else {
				Mix_PauseMusic();
			}
			toggleMusic = false;
		}
	}
}

void MenuLayer::keysToControls(SDL_Event event) {
	if (event.type == SDL_KEYDOWN) {
		int code = event.key.keysym.sym;
		
		switch (code)
		{
		case SDLK_ESCAPE: // Esc
			game->loopActive = false;
			break;
		case SDLK_1:
			game->scale();
			break;
		case SDLK_SPACE:
			controlContinue = true;
			break;
		case SDLK_m:
			toggleMusic = true;
			break;
		}
		
	}
}

void MenuLayer::mouseToControls(SDL_Event event) {
	// Modificación de las coordenadas por posible escalado
	float motionX = event.motion.x / game->scaleLower;
	float motionY = event.motion.y / game->scaleLower;

	// Cada vez que hacen click
	if (event.type == SDL_MOUSEBUTTONDOWN) {
		// Click sobre el botón de Jugar
		if (buttonJugar->containsPoint(motionX, motionY)) {
			controlContinue = true;
			this->jugarSound->play();
		}

		// Click sobre el botón de Salir
		if (buttonSalir->containsPoint(motionX, motionY)) {
			exit = true;
			this->exitSound->play();
		}
	}
}
