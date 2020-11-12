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
#include "EnemyGenerator.h"
#include "Tower.h"
#include "CollisionEngine.h"

#include <list>
#include <map>

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

	list<Tile*> pathTiles;
	list<Tile*> shootPoints;

	int mapWidth; // Ancho del mapa
	int mapHeight; // Alto del mapa

	// Motor de movimientos / físicas
	Space* space;

	// Motor de colisiones
	CollisionEngine* collisionEngine;

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

	// Puntuación
	Text* textPoints;
	int points;

	// Audio
	Audio* audioBackground;

	// Pausa y mensajes
	Actor* message;
	bool pause;
	bool controlContinue;

	// Trayectorias
	PathManager* pathManager;

	// Mapa
	MapManager* mapManager;

	// Generadores de enemigos
	map<int,EnemyGenerator*> enemyGenerators;

	// Torres
	map<int, Tower*> towers;
private:
	void addNewEnemy();
	void destroyEnemies();
	void destroyProjectiles();
};

