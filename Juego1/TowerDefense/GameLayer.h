#pragma once

#include "Layer.h"
#include "Player.h"
#include "Background.h"
#include "Enemy.h"
#include "Projectile.h"
#include "Text.h"
#include "Audio.h"
#include "Tile.h"
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
#include "Gem.h"
#include "GemGenerator.h"
#include "UIPowerUp.h"
#include "TowerManager.h"
#include "UIHordeCounter.h"

#include <list>
#include <map>
#include <queue>
#include "PowerUp.h"
#include "PowerUpGenerator.h"
#include "PowerUpInventory.h"


#define ENEMY_SPAWN_TIME 110
#define ENEMY_SPAWN_FREQUENCY 5
#define HORDE_DELAY 120 // Delay de ticks entre cada horda



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

	// Motor de colisiones
	CollisionEngine* collisionEngine;

	Player* player;
	Background* background;

	// Controles
	bool controlShoot = false;
	int controlMoveX = 0;
	int controlMoveY = 0;

	
	// Eventos de rat�n
	float mouseX;
	float mouseY;
	bool mouseClick;
	float xClick;
	float yClick;
	bool mouseHold;
	bool mouseReleased;

	// Drag & Drop
	// Torreta actualmente seleccionada
	Turret* selectedTurret;
	// PowerUp actualmente seleccionado
	PowerUp* selectedPowerUp;

	// Lista de enemigos
	list<Enemy*> enemies;
	// Lista de proyectiles
	list<Projectile*> projectiles;

	int newEnemyTime = 0;

	 // Enemigos eliminados en la horda actual
	int leftEnemies = 0; // enemigos de la horda actual que quedan vivos

	// Mapas
	queue<string> maps;

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
	TowerManager* towerManager;

	// Gestor de construcci�n
	ConstructionManager* constructionManager;

	// Gestor de compra de torretas
	ShopManager* shopManager;

	// UI
	UITextIcon* uiRecursos;
	UITextIcon* uiLeftEnemies;
	PowerUpInventory* powerUpInventory;
	UIHordeCounter* uiHordeCounter;

	// Hordas de enemigos
	Horde* currentHorde;
	queue<Horde*> hordes;
	
	// Gemas
	list<Gem*> gems;
	GemGenerator* gemGenerator;

	// PowerUps
	PowerUpGenerator* powerUpGenerator;
	list<PowerUp*> powerUps;
	
	// Sonido
	// Background music
	Mix_Music* backgroundMusic;



private:

	/// <summary>
	/// Este m�todo carga las referencias a los distintos objetos obtenidas por
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
	/// A�ade recursos recolectables de forma aleatoria
	/// cada cierto n�mero de ticks
	/// </summary>
	//void addResourceCollectable();

	/// <summary>
	/// Hace un pop de la cola FIFO de hordas para obtener
	/// y devolver la siguiente horda de enemigos.
	/// </summary>
	/// <returns></returns>
	Horde* getNextHorde();

	/// <summary>
	/// Comprueba si el jugador ha ganado. El jugador gana cuando se han superado
	/// todas las hordas de enemigos y ya no queda ninguno.
	/// </summary>
	/// <returns></returns>
	bool checkWin();

	/// <summary>
	/// Inicializa la cola FIFO con los strings
	/// de los mapas
	/// </summary>
	void initMaps();

	/// <summary>
	/// Devuelve un string que representa el nombre del fichero
	/// del siguiente mapa a cargar.
	/// </summary>
	/// <returns></returns>
	string getNextMap();


	// M�todos para destruir actores
	void destroyEnemies();
	void destroyProjectiles();
	void destroyGems();
	void destroyTowers();
	void destroyPowerUps();
};

