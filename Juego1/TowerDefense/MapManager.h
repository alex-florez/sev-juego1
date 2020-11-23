#pragma once

#include <iostream>
#include <list>
#include <map>
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
	ConstructionManager* getConstructionManager();
	list<Enemy*> getEnemies();
	list<Tile*> getPathTiles();
	EnemyGenerator* getEnemyGenerator();
	map<int, Tower*> getTowers();
	map<int, Horde*> getHordes();
	int getMapHeight();
	int getMapWidht();
	void show();

private:
	Game* game;
	EnemyGenerator* enemyGenerator; // Generador de enemigos.
	map<int, Tower*> towers; // Torres para defender
	map<int, Horde*> hordes; // Hordas de enemigos
	char map[FILE_ROWS][FILE_COLS]; // matriz con los caracteres del mapa.
	PathManager* pathManager; // Gestor de trayectorias
	ConstructionManager* constructionManager; // Gestor de construcción.
	list<Tile*> pathTiles; // Tiles que representan los distintos caminos
	
	
	int mapHeight; // Altura del mapa
	int mapWidth; // Anchura del mapa

	void parseObjects();
	void loadMapObject(char character, int i, int j);

};

