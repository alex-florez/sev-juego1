#include "MapManager.h"


MapManager::MapManager(Game* game) {
	this->game = game;
	this->pathManager = new PathManager();
	this->constructionManager = new ConstructionManager(game, nullptr);
}


list<Tile*> MapManager::getPathTiles() {
	return this->pathTiles;
}

ConstructionManager* MapManager::getConstructionManager() {
	return this->constructionManager;
}


PathManager* MapManager::getPathManager() {
	return this->pathManager;
}

map<int, EnemyGenerator*> MapManager::getEnemyGenerators() {
	return this->enemyGenerators;
}

map<int, Tower*> MapManager::getTowers() {
	return this->towers;
}

int MapManager::getMapHeight() {
	return this->mapHeight;
}

int MapManager::getMapWidht() {
	return this->mapWidth;
}


void MapManager::loadMap(string filename) {
	char character;
	int totalLines = 0;
	string line;
	ifstream streamFile(filename.c_str()); // No es una función, es el constructor de ifstream
	if (!streamFile.is_open()) {
		cout << "Falla abrir el fichero de mapa" << endl;
		return;
	}
	else {
		// Por línea
		for (int i = 0; getline(streamFile, line); i++) {
			totalLines++;
			istringstream streamLine(line);
			mapWidth = line.length() * TILE_WIDTH; // Ancho del mapa en pixels
			// Por carácter (en cada línea)
			for (int j = 0; !streamLine.eof(); j++) {
				streamLine >> character; // Leer character
				map[i][j] = character;
				//loadMapObject(character, i, j);
			}
		}
		mapHeight = totalLines * 32;
	}

	streamFile.close();
	parseObjects(); // Parsear los objetos
}


void MapManager::parseObjects() {
	for (int i = 0; i < FILE_ROWS; i++) {
		for (int j = 0; j < FILE_COLS; j++) {
			loadMapObject(map[i][j], i, j);
		}
	}
}

void MapManager::loadMapObject(char character, int i, int j) {
	float x = TILE_WIDTH / 2 + j * TILE_WIDTH; // x central
	float y = TILE_HEIGHT + i * TILE_HEIGHT; // y suelo

	switch (character) {
		case '1':
		case '2': 
		case '3': {
			Tile* tile = new Tile("res/caja_madera.png", x, y, game);
			tile->y = tile->y - tile->height / 2;
			pathTiles.push_back(tile);
			int pathId = character - '0';
			this->pathManager->addPointToPath(pathId, new Point(j,i));
			break;
		}
		case 'E': {
			int pathId = map[i][j - 1] - '0'; // Obtenemos el id de la trayectoria que seguirán los enemigos de este generador
			this->enemyGenerators[pathId] = new EnemyGenerator(pathId, j, i, 100, 2, game);
			break;
		}
		case 'C': {
			ConstructionTile* constructionTile = new ConstructionTile(x, y, game);
			constructionTile->y = constructionTile->y - constructionTile->height / 2;
			this->constructionManager->addConstructionTile(constructionTile);
			break;
		}
		case 'T': {
			Tower* tower = new Tower("res/tower.png", x, y, game);
			tower->y = tower->y - tower->height / 2;
			int id = map[i][j + 1] - '0';
			tower->pathId = id;
			towers[id] = tower;
			break;
		}
	}
}

void MapManager::show() {
	for (int i = 0; i < FILE_ROWS; i++) {
		for (int j = 0; j < FILE_COLS; j++) {
			cout << map[i][j] << " ";
		}
		cout << endl;
	}
}