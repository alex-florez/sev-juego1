#include "MapManager.h"


MapManager::MapManager(Game* game) {
	this->game = game;
	this->pathManager = new PathManager();
}


list<Tile*> MapManager::getPathTiles() {
	return this->pathTiles;
}

list<Tile*> MapManager::getShootPoints() {
	return this->shootPoints;
}

list<Enemy*> MapManager::getEnemies() {
	return this->enemies;
}

PathManager* MapManager::getPathManager() {
	return this->pathManager;
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
			mapWidth = line.length() * 40; // Ancho del mapa en pixels
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
	parseObjects();
}


void MapManager::parseObjects() {
	for (int i = 0; i < FILE_ROWS; i++) {
		for (int j = 0; j < FILE_COLS; j++) {
			loadMapObject(map[i][j], i, j);
		}
	}
}

void MapManager::loadMapObject(char character, int i, int j) {
	float x = 40 / 2 + j * 40; // x central
	float y = 40 + i * 40; // y suelo

	switch (character) {
		case '1': {
			Tile* tile = new Tile("res/caja_madera.png", x, y, game);
			tile->y = tile->y - tile->height / 2;
			pathTiles.push_back(tile);
			this->pathManager->addPointToPath(1, new Point(j, i));
			break;
		}
		//case '#': {
		//	Tile* tile = new Tile("res/bloque_tierra.png", x, y, game);
		//	// modificación para empezar a contar desde el suelo.
		//	tile->y = tile->y - tile->height / 2;
		//	tiles.push_back(tile);
		//	space->addStaticActor(tile);
		//	break;
		//}
		case 'E': {
			Enemy* enemy = new Enemy(x, y, game);
			enemy->y = enemy->y - enemy->height / 2;
			enemy->pathId = 1;
			enemies.push_back(enemy);
			//space->addDynamicActor(enemy);
			enemy->nextPoint = new Point(15, 5);
			enemy->lastPoint = nullptr;
			break;
		}
		//case 'C': {
		//	cup = new Tile("res/copa.png", x, y, game);
		//	cup->y = cup->y - cup->height / 2;
		//	break;
		//}

		case 'A': {
			Tile* shootPoint = new Tile("res/caja_madera.png", x, y, game);
			shootPoint->y = shootPoint->y - shootPoint->height / 2;
			shootPoints.push_back(shootPoint);
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