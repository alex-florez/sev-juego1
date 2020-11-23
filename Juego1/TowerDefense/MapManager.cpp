#include "MapManager.h"


MapManager::MapManager(Game* game) {
	this->game = game;
	this->pathManager = new PathManager();
	this->constructionManager = new ConstructionManager(game, nullptr);
	this->enemyGenerator = new EnemyGenerator(game);
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

EnemyGenerator* MapManager::getEnemyGenerator() {
	return this->enemyGenerator;
}

map<int, Tower*> MapManager::getTowers() {
	return this->towers;
}

map<int, Horde*> MapManager::getHordes() {
	// Cargar las hordas desde el fichero
	this->hordes[1] = new Horde(4, 70, 100);
	this->hordes[2] = new Horde(7, 50, 70);
	this->hordes[3] = new Horde(10, 40, 60);
	return this->hordes;
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
	ifstream streamFile(filename.c_str()); // No es una funci�n, es el constructor de ifstream
	if (!streamFile.is_open()) {
		cout << "Falla abrir el fichero de mapa" << endl;
		return;
	}
	else {
		// Por l�nea
		for (int i = 0; getline(streamFile, line); i++) {
			totalLines++;
			istringstream streamLine(line);
			mapWidth = line.length() * TILE_WIDTH; // Ancho del mapa en pixels
			// Por car�cter (en cada l�nea)
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
			int pathId = map[i][j - 1] - '0'; // Obtenemos el id de la trayectoria que seguir�n los enemigos de este generador
			this->enemyGenerator->spawnPoints[pathId] = new Point(j, i);
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