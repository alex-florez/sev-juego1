#include "MapManager.h"


MapManager::MapManager(Game* game) {
	this->game = game;
	this->pathManager = new PathManager();
	this->towerManager = new TowerManager(game);
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

TowerManager* MapManager::getTowerManager()
{
	return this->towerManager;
}

EnemyGenerator* MapManager::getEnemyGenerator() {
	return this->enemyGenerator;
}


queue<Horde*> MapManager::getHordes() {
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
	ifstream streamFile(filename.c_str()); // No es una función, es el constructor de ifstream
	if (!streamFile.is_open()) {
		cout << "Falla abrir el fichero de mapa" << endl;
		return;
	}
	else {
		// Primera linea de configuración
		getline(streamFile, line);
		parseConfigLine(line);
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
		mapHeight = (totalLines-1) * 32;
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
			this->enemyGenerator->addSpawnPoint(pathId, new Point(j, i));
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
			this->towerManager->add(id, tower);
			break;
		}
	}
}

void MapManager::parseConfigLine(string line) {
	list<string> data = split(line, ";");
	int index = 1;
	int maxSpawnFreq = 100;
	int minSpawnFreq = 70;
	for (auto const& d : data) {
		queue<char> enemySequence = getCharQueue(d);
		this->hordes.push(new Horde(index, enemySequence, enemySequence.size(), minSpawnFreq, maxSpawnFreq));
		index++;
		maxSpawnFreq -= 20;
		minSpawnFreq -= 20;
	}
}

queue<char> MapManager::getCharQueue(string data) {
	queue<char> result;
	list<string> fragments = split(data, ",");
	for (auto const& s : fragments) {
		char type = s.at(0);
		int n = s.at(1) - '0';
		for (int i = 0; i < n; i++) {
			result.push(type);
		}
	}
	return result;
}


list<string> MapManager::split(string line, string delimiter) {
	list<string> data;
	size_t pos = 0;
	while ((pos = line.find(delimiter)) != string::npos) {
		data.push_back(line.substr(0, pos));
		line.erase(0, pos + delimiter.length());
	}
	data.push_back(line);
	return data;
}

void MapManager::show() {
	for (int i = 0; i < FILE_ROWS; i++) {
		for (int j = 0; j < FILE_COLS; j++) {
			cout << map[i][j] << " ";
		}
		cout << endl;
	}
}