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
#include "Turret.h"
#include "ShopManager.h"
#include "UITextIcon.h"
#include "Horde.h"
#include "RGB.h"

#include <list>
#include <map>
#include <queue>
#include "Resources.h"

#define ENEMY_SPAWN_TIME 110
#define ENEMY_SPAWN_FREQUENCY 5
#define HORDE_DELAY 120 // Delay de ticks entre cada horda
#define RESOURCES_SPAWN_FREQUENCY 300


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

	
	// Evento de click
	bool mouseClick;
	float xClick;
	float yClick;

	// Lista de enemigos
	list<Enemy*> enemies;
	// Lista de proyectiles
	list<Projectile*> projectiles;

	int newEnemyTime = 0;

	// Puntuación
	Text* textPoints;
	int points;

	 // Enemigos eliminados en la horda actual
	int leftEnemies = 0; // enemigos de la horda actual que quedan vivos


	// Audio
	Audio* audioBackground;

	// Pausa y mensajes
	Actor* message;
	bool pause;
	bool controlContinue;

	// Gestor de Trayectorias
	PathManager* pathManager;

	// Mapa
	MapManager* mapManager;

	// Generador de enemigos
	EnemyGenerator* enemyGenerator;

	// Torres
	map<int, Tower*> towers;

	// Gestor de construcción
	ConstructionManager* constructionManager;

	// Gestor de compra de torretas
	ShopManager* shopManager;

	// UI
	UITextIcon* uiRecursos;
	UITextIcon* uiLeftEnemies;

	// Hordas de enemigos
	Horde* currentHorde;
	queue<Horde*> hordes;
	

	// Recursos coleccionables
	list<Resources*> randomResources;
	int ticksUntilNextResourcesSpawn = RESOURCES_SPAWN_FREQUENCY;


private:

	/// <summary>
	/// Este método carga las referencias a los distintos objetos obtenidas por
	/// el MapManager tras cargar el mapa desde el fichero.
	/// </summary>
	void loadEntities();

	/// <summary>
	/// Devuelve true si la horda actual ha terminado, es decir,
	/// se han eliminado a todos los enemigos.
	/// </summary>
	/// <returns></returns>
	bool hordeHasFinished();

	/// <summary>
	/// Añade recursos recolectables de forma aleatoria
	/// cada cierto número de ticks
	/// </summary>
	void addResourceCollectable();

	/// <summary>
	/// Hace un pop de la cola FIFO de hordas para obtener
	/// y devolver la siguiente horda de enemigos.
	/// </summary>
	/// <returns></returns>
	Horde* getNextHorde();

	void addNewEnemy();
	void destroyEnemies();
	void destroyProjectiles();
};

