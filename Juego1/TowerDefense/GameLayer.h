#pragma once

#include "Layer.h"
#include "Player.h"
#include "Background.h"
#include "Enemy.h"
#include "Projectile.h"
#include "Text.h"
#include "Audio.h"
#include "Tile.h"
#include "Space.h"
#include "Path.h"
#include "PathManager.h"
#include "MapManager.h"

#include <list>
#include <fstream> // Leer ficheros
#include <sstream> // Leer l�neas / strings

#define ENEMY_SPAWN_TIME 110
#define ENEMY_SPAWN_FREQUENCY 5		


class GameLayer : public Layer
{
public:
	GameLayer(Game* game);
	void init() override;
	void processControls() override;
	void update() override;
	void draw() override;
	void keysToControls(SDL_Event event);
	void mouseToControls(SDL_Event event); // Uso del mouse

	// M�todos para cargar el mapa y los objetos del mismo
	void loadMap(string name);
	void loadMapObject(char character, int i, int j);

	list<Tile*> pathTiles;
	list<Tile*> shootPoints;

	int mapWidth; // Ancho del mapa
	int mapHeight; // Alto del mapa
	list<Tile*> tiles; // Lista de tiles.

	// Motor de movimientos / f�sicas
	Space* space;

	Player* player;
	Background* background;
	Actor* backgroundPoints;

	// Controles
	bool controlShoot = false;
	int controlMoveX = 0;
	int controlMoveY = 0;

	// Lista de enemigos
	list<Enemy*> enemies;
	// Lista de proyectiles
	list<Projectile*> projectiles;

	int newEnemyTime = 0;
	int killedEnemies = 0;


	// Puntuaci�n
	Text* textPoints;
	int points;

	// Audio
	Audio* audioBackground;

	// Copa de final de nivel
	Tile* cup;

	// Pausa y mensajes
	Actor* message;
	bool pause;
	bool controlContinue;

	// Trayectorias
	PathManager* pathManager;

	// Mapa
	MapManager* mapManager;


private:
	void addNewEnemy();
	void destroyEnemies();
	void destroyProjectiles();
};

