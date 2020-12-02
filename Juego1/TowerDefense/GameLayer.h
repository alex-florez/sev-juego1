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

	Player* player; // Jugador
	Background* background; // Fondo
	
	// Coordenadas de ratón
	float mouseX;
	float mouseY;
	// Eventos de ratón
	bool mouseClick;
	bool mouseHold;
	bool mouseReleased;

	// Drag & Drop
	Turret* selectedTurret; // Torreta actualmente seleccionada
	PowerUp* selectedPowerUp; // PowerUp actualmente seleccionado

	// Lista de enemigos
	list<Enemy*> enemies;
	// Lista de proyectiles
	list<Projectile*> projectiles;

	int leftEnemies = 0; // enemigos de la horda actual que quedan vivos

	// Mapas
	queue<string> maps;

	// Pausa y mensajes
	Actor* message;
	bool pause;
	bool reset; // Indica si se debe resetear el juego (por ejemplo cuando el jugador pierde, o gana)

	// Gestor de Trayectorias
	PathManager* pathManager;

	// Mapa
	MapManager* mapManager;

	// Generador de enemigos
	EnemyGenerator* enemyGenerator;

	// Torres
	TowerManager* towerManager;

	// Gestor de construcción
	ConstructionManager* constructionManager;

	// Gestor de compra de torretas
	ShopManager* shopManager;

	// UI
	UITextIcon* uiRecursos;
	UITextIcon* uiLeftEnemies;
	UITextIcon* uiInfiltratedEnemies; // Indica el nº de enemigos que se han colado.
	PowerUpInventory* powerUpInventory;
	UIHordeCounter* uiHordeCounter;

	// Hordas de enemigos
	Horde* currentHorde;
	queue<Horde*> hordes;

	// Nº máximo de enemigos infiltrados
	int maxInfiltratedEnemies;
	int infiltratedEnemies; // Enemigos infiltrados hasta el momento en este nivel.
	
	// Gemas
	list<Gem*> gems;
	GemGenerator* gemGenerator;

	// PowerUps
	PowerUpGenerator* powerUpGenerator;
	list<PowerUp*> powerUps;
	
	// Sonido
	// Background music
	Mix_Music* backgroundMusic;
	SoundEffect* upgradeSound;



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
	/// Devuelve true si el jugador ha perdido
	/// la partida, bien porque se haya quedado sin torres, o porque
	/// el nº de enemigos infiltrados supere al máximo permitido.
	/// </summary>
	/// <returns></returns>
	bool checkLoose();

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


	/// <summary>
	/// Método invocado cada vez que se pulse
	/// la tecla 'p', para pausar el juego y mostrar un mensaje
	/// de cómo jugar.
	/// </summary>
	void pauseGame();

	// Métodos para destruir actores
	void destroyEnemies();
	void destroyProjectiles();
	void destroyGems();
	void destroyTowers();
	void destroyPowerUps();
};

