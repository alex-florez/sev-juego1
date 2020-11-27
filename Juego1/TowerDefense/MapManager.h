#pragma once

#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <fstream> // Leer ficheros
#include <sstream> // Leer líneas / strings


#include "PathManager.h"
#include "Enemy.h"
#include "Tile.h"
#include "EnemyGenerator.h"
#include "Tower.h"
#include "ConstructionTile.h"
#include "ConstructionManager.h"
#include "Horde.h"
#include "TowerManager.h"

using namespace std;

#define FILE_ROWS 15
#define FILE_COLS 22

/// <summary>
/// Clase para gestionar la carga de los objetos del mapa
/// a partir de un fichero.
/// </summary>
class MapManager
{
public:
	MapManager(Game* game);
	void loadMap(string filename);
	PathManager* getPathManager();
	TowerManager* getTowerManager();
	ConstructionManager* getConstructionManager();
	list<Tile*> getPathTiles();
	EnemyGenerator* getEnemyGenerator();
	map<int, Tower*> getTowers();
	queue<Horde*> getHordes();
	int getMapHeight();
	int getMapWidht();
	void show();

private:
	Game* game;
	EnemyGenerator* enemyGenerator; // Generador de enemigos.
	TowerManager* towerManager; // gestor de torres;
	char map[FILE_ROWS][FILE_COLS]; // matriz con los caracteres del mapa.
	PathManager* pathManager; // Gestor de trayectorias
	ConstructionManager* constructionManager; // Gestor de construcción.
	list<Tile*> pathTiles; // Tiles que representan los distintos caminos
	queue<Horde*> hordes; // Hordas de enemigos
	
	int mapHeight; // Altura del mapa
	int mapWidth; // Anchura del mapa

	void parseObjects();
	/// <summary>
	/// Se encarga de parsear la 1a línea del fichero que
	/// contiene la configuración de las hordas del mapa.
	/// </summary>
	void parseConfigLine(string line);
	void loadMapObject(char character, int i, int j);
	list<string> split(string line, string delimiter);
	queue<char> getCharQueue(string data);
};

