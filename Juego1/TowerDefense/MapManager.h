#pragma once

#include <iostream>
#include <list>
#include <fstream> // Leer ficheros
#include <sstream> // Leer líneas / strings


#include "PathManager.h"
#include "Enemy.h"
#include "Tile.h"
#include "EnemyGenerator.h"


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
	EnemyGenerator* getEnemyGenerator();
	int getMapHeight();
	int getMapWidht();
	void show();

private:
	Game* game;
	char map[FILE_ROWS][FILE_COLS]; // matriz con los caracteres del mapa.
	PathManager* pathManager; // Gestor de trayectorias
	EnemyGenerator* enemyGenerator1; // Generador de enemigos
	list<Enemy*> enemies; // lista de enemigos
	list<Tile*> pathTiles; // Tiles que representan los distintos caminos 
	
	list<Tile*> shootPoints;

	int mapHeight; // Altura del mapa
	int mapWidth; // Anchura del mapa

	void parseObjects();
	void loadMapObject(char character, int i, int j);

};

