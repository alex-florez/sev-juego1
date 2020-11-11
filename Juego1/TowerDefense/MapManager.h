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
	list<Enemy*> getEnemies();
	list<Tile*> getPathTiles();
	list<Tile*> getShootPoints();
	map<int, EnemyGenerator*> getEnemyGenerators();
	map<int, Tower*> getTowers();
	int getMapHeight();
	int getMapWidht();
	void show();

private:
	Game* game;
	map<int, EnemyGenerator*> enemyGenerators; // Generadores de enemigos
	map<int, Tower*> towers; // Torres para defender
	char map[FILE_ROWS][FILE_COLS]; // matriz con los caracteres del mapa.
	PathManager* pathManager; // Gestor de trayectorias
	list<Tile*> pathTiles; // Tiles que representan los distintos caminos 
	list<Tile*> shootPoints;
	

	int mapHeight; // Altura del mapa
	int mapWidth; // Anchura del mapa

	void parseObjects();
	void loadMapObject(char character, int i, int j);

};

