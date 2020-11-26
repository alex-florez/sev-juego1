#include "GameLayer.h"


void markEnemyForDelete(Enemy* enemy, list<Enemy*>& deleteList);
void markProjectileForDelete(Projectile* projectile, list<Projectile*>& deleteList);
void markTileForDelete(Tile* tile, list<Tile*>& deleteList);
void markTowerForDelete(Tower* tower, list<Tower*>& deleteList);
void markGemForDelete(Gem* gem, list<Gem*>& deleteList);


GameLayer::GameLayer(Game* game)
	: Layer(game) { // Se hace una llamada al constructor del padre

	pause = false;
	message = new Actor("res/mensaje_como_jugar.png", WIDTH*0.5, HEIGHT*0.5,
		WIDTH, HEIGHT, game);

	init();
}

void GameLayer::init() {
	// Puntuaci�n
	points = 0;
	//textPoints = new Text("hola", WIDTH * 0.92, HEIGHT * 0.05, game);
	//textPoints->content = to_string(points);
	backgroundPoints = new Actor("res/icono_puntos.png", WIDTH * 0.85, HEIGHT * 0.05, 24, 24, game);

	space = new Space(0); // Instanciamos el motor de f�sicas con gravedad.

	// Destruir posibles objetos existentes
	delete player;
	destroyEnemies();
	destroyProjectiles();

	background = new Background("res/grass.jpg", WIDTH * 0.5, HEIGHT * 0.5, game);

	// Map Manager
	mapManager = new MapManager(game);

	// Collision engine
	collisionEngine = new CollisionEngine();

	// Enemigos
	enemies.clear(); // Vaciar la lista de enemigos, por si se reinicia el juego

	// Proyectiles
	projectiles.clear();

	// Torretas
	//turrets.clear();

	// Torres
	towers.clear();


	// Semilla aleatoria para generar n�meros aleatorios
	srand(SDL_GetTicks());

	this->mouseClick = false;
	this->mouseHold = false;
	this->mouseReleased = false;

	this->selectedTurret = nullptr;

	// Audio de fondo
	audioBackground = new Audio("res/musica_ambiente.mp3", true);
	//audioBackground->play();

	// Botones de la interfaz
	//buttonJump = new Actor("res/boton_salto.png", WIDTH*0.9, HEIGHT * 0.55, 100, 100, game);
	//buttonShoot = new Actor("res/boton_disparo.png", WIDTH * 0.75, HEIGHT * 0.83, 100, 100, game);

	RGB* color1 = new RGB(255, 255, 23);
	uiRecursos = new UITextIcon(0.85 * WIDTH, 0.04 * HEIGHT, 29, 41, 50, color1, "res/gemsIcon.png", "", game);
	uiLeftEnemies = new UITextIcon(0.75 * WIDTH, 0.04 * HEIGHT, 32, 32, 38, color1, "res/leftEnemiesIcon.png", "0", game);

	player = new Player(0, 0, game);

	// Gestor de compra
	this->shopManager = new ShopManager(player, game);

	mapManager->loadMap("res/mapa-2.txt");
	loadEntities();

	// inicializar el motor de colisiones
	this->collisionEngine->addTowers(&this->towers);
	this->collisionEngine->addEnemies(&this->enemies);
	this->collisionEngine->addProjectiles(&this->projectiles);
	this->collisionEngine->addPlayer(player);

	// Horda inicial
	this->currentHorde = getNextHorde();
	// Establecer la ronda inicial al generador de enemigos
	this->enemyGenerator->setNextHorde(this->currentHorde, 0);
	this->leftEnemies = this->currentHorde->totalNumberOfEnemies;

	this->gemGenerator = new GemGenerator(game);


}


/**
* M�todo encargado de actualizar todos los elementos del juego.
**/
void GameLayer::update() {

	list<Enemy*> deleteEnemies; // Enemigos a eliminar
	list<Projectile*> deleteProjectiles; // Proyectiles a eliminar
	list<Tower*> deleteTowers; // Torres a eliminar
	list<Gem*> deleteGems; // Gemas recolectables a eliminar

	if (pause) {
		return;
	}

	//// Comprobamos si el jugador colisiona con el elemento de final de nivel
	//if (cup->isOverlap(player)) {
	//	game->currentLevel++;
	//	if (game->currentLevel > game->finalLevel) {
	//		game->currentLevel = 0;
	//	}
	//	message = new Actor("res/mensaje_ganar.png", WIDTH*0.5, HEIGHT*0.5, WIDTH, HEIGHT, game);
	//	pause = true;
	//	init();
	//	return;
	//}

	// Actualizamos todos los actores din�micos
	//space->update();

	// Actualizar el motor de colisiones
	collisionEngine->update();

	// Actualizar generador de enemigos
	Enemy* newEnemy = this->enemyGenerator->createEnemy();
	if (newEnemy != nullptr) enemies.push_back(newEnemy);
	

	//player->update();
	// Actualizamos los enemigos
	for (auto const& enemy : enemies) {
		pathManager->update(enemy); // Actualizar trayectoria del enemigo
		enemy->update(); // Actualizar estado del enemigo.
		// Enemigo a la izquierda de la pantalla
		if (enemy->x + enemy->width / 2 <= 0) {
			markEnemyForDelete(enemy, deleteEnemies);
		}
		else if (enemy->state == Enemy::EnemyState::DEAD) { // Enemigo est� muerto -> eliminarlo
			markEnemyForDelete(enemy, deleteEnemies);
		}
		//} else if (player->isOverlap(enemy)) { // Colisi�n con el jugador
		//	// Comprobamos si el player ha saltado encima del enemigo
		//	if (player->isOver(enemy)) {
		//		player->audioJumpOverEnemy->play(); // Reproducir sonido de aplastamiento
		//		markEnemyForDelete(enemy, deleteEnemies);
		//	}
		//	else {
		//		player->loseLife();
		//		if (player->lifes <= 0) { // Jugador sin vidas
		//			init();
		//			return; // Se reinicia el juego.
		//		}
		//	}
		//}
	}



	// Actualizar las torretas
	for (auto const& turret : this->constructionManager->turrets) {
		turret->update(this->enemies); // Escanear enemigos
		Projectile* p = turret->shoot(); // Realizar disparo
		if (p != nullptr) {
			projectiles.push_back(p);
		}
	}

	// Actualizar los proyectiles
	for (auto const& projectile : projectiles) {
		projectile->update();
		if (!projectile->isInRender()) { // Proyectil fuera del render
			markProjectileForDelete(projectile, deleteProjectiles);
		}
		else if (projectile->impacted) { // Proyectiles que ya han impactado.
			markProjectileForDelete(projectile, deleteProjectiles);
		}
	}

	// Actualizar torres
	for (auto const& pair : towers) {
		pair.second->update();
		// Si la torre est� destruida entonces se elimina
		if (pair.second->state == Tower::TowerState::DESTROYED) {
			markTowerForDelete(pair.second, deleteTowers);
		}
	}

	// Enemigos restantes
	if (this->currentHorde != nullptr) // Actualizar el n� de enemigos restantes
		leftEnemies = this->currentHorde->totalNumberOfEnemies - this->player->killedEnemiesInActualHorde;

	// Actualizar hordas
	if (this->currentHorde != nullptr) { // A�n no se han terminado las hordas...
		if (this->hordeHasFinished()) { // Horda finalizada
			this->currentHorde = getNextHorde();
			this->player->killedEnemiesInActualHorde = 0;
			if (this->currentHorde != nullptr) {
				this->enemyGenerator->setNextHorde(this->currentHorde, HORDE_DELAY);
				this->leftEnemies = this->currentHorde->totalNumberOfEnemies;
			}
		}
	}

	// Recolectables
	//this->addResourceCollectable();
	
	Gem* newGem = this->gemGenerator->createGem();
	if (newGem != nullptr)
		gems.push_back(newGem);

	// Eliminar recolectables ya recogidos
	for (auto const& gem : gems) {
		if (gem->collected)
			markGemForDelete(gem, deleteGems);
	}

	// Actualizamos los proyectiles
	//for (auto const& projectile : projectiles) {
	//	projectile->update();
	//	// Proyectil a la derecha de la pantalla o proyectil sin velocidad (impacto con alg�n elemnto est�tico)
	//	if (!projectile->isInRender(scrollX, scrollY) || projectile->vx == 0) {
	//		markProjectileForDelete(projectile, deleteProjectiles);
	//	}

	//	// Comprobamos colisiones de proyectiles con tiles 
	//	for (auto const& tile : tiles) {
	//		if (tile->isOverlap(projectile)) {
	//			if (tile->isDestroyable()) {// Si el tile es destruible, se elimina
	//				markTileForDelete(tile, deleteTiles);
	//				markProjectileForDelete(projectile, deleteProjectiles);
	//			}	
	//		}
	//	}
	//}

	// Colisiones entre enemigos y proyectiles
	//for (auto const& enemy : enemies) {
	//	for (auto const& projectile : projectiles) {
	//		if (enemy->isOverlap(projectile)) {
	//			// Incrementar el n� de enemigos eliminados
	//			killedEnemies++;
	//			// Incrementar puntuaci�n
	//			points++;
	//			textPoints->content = to_string(points);
	//			markProjectileForDelete(projectile, deleteProjectiles);
	//			//markEnemyForDelete(enemy, deleteEnemies);
	//			enemy->impacted();
	//		}
	//	}
	//}


	// Actualizar UI
	this->uiRecursos->text->content = to_string(this->player->availableResources);
	this->uiLeftEnemies->text->content = to_string(this->leftEnemies);

	for (auto const& enemy : enemies) { // Marcamos para eliminar aquellos enemigos en el estado muerto.
		//if (enemy->state == game->stateDead) {
		//	markEnemyForDelete(enemy, deleteEnemies);
		//}
	}

	// Eliminar torres destruidas
	for (auto const& tower : deleteTowers) {
		towers.erase(tower->pathId);
		delete tower;
	}
	deleteTowers.clear();

	// Eliminamos los proyectiles y enemigos necesarios
	for (auto const& delEnemy : deleteEnemies) {
		enemies.remove(delEnemy);
		space->removeDynamicActor(delEnemy); // Eliminamos al enemigo del motor de f�sicas.
		delete delEnemy; // Se destruye el enemigo.
	}
	deleteEnemies.clear();

	for (auto const& delProjectile : deleteProjectiles) {
		projectiles.remove(delProjectile);
		space->removeDynamicActor(delProjectile);
		delete delProjectile; // Se destruye el proyectil.
	}
	deleteProjectiles.clear();

	for (auto const& delGem : deleteGems) {
		gems.remove(delGem);
		delete delGem;
	}
	deleteGems.clear();
}


void GameLayer::processControls() {
	// obtener controles
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		// Cambio autom�tico del input
		switch (event.type)
		{
		case SDL_QUIT: // Se hace click en la X para cerrar la ventana
			game->loopActive = false;
			break;
		case SDL_KEYDOWN:
			game->input = GameInputType::KEYBOARD;
			break;
		case SDL_MOUSEBUTTONDOWN:
			game->input = GameInputType::MOUSE;
			break;
		}

		if (game->input == GameInputType::KEYBOARD) {
			keysToControls(event);
		}
		if (game->input == GameInputType::MOUSE) {
			mouseToControls(event);
		}
	}
	// procesar controles
	// Despausar el juego
	if (controlContinue) {
		pause = false;
		controlContinue = false;
	}

	// Drag & drop
	if (mouseClick) {
		cout << "Mouse clicked!" << endl;
		// Comprobar la compra de torretas
		this->selectedTurret = this->shopManager->purchase(mouseX, mouseY);

		// Comprobar la recolecci�n de items
		for (auto const& gem : gems) {
			if (gem->containsPoint(xClick, yClick)) {
				gem->collected = true;
				player->availableResources += gem->value;
			}
		}
		mouseClick = false;
	}
		

	if (mouseReleased) {
		cout << "Mouse released!" << endl;
		this->constructionManager->construct(mouseX, mouseY, this->selectedTurret);
		this->selectedTurret = nullptr;
		this->shopManager->clearPurchase();
		mouseReleased = false;
	}
		
	if (mouseHold) {
		cout << "Mouse hold!" << endl;
		if (this->selectedTurret != nullptr) {
			this->selectedTurret->x = this->mouseX;
			this->selectedTurret->y = this->mouseY;
		}
	}
		

	// Se ha hecho click con el rat�n
	//if (mouseClick) {
	//	// Delegar a los managers el control del click
	//	this->constructionManager->construct(xClick, yClick, this->shopManager->getPurchasedTurret()); // Construir torreta
	//	this->shopManager->purchase(xClick, yClick); // Comprar torreta
	//	// Click sobre alguna gema
	//	for (auto const& gem : gems) {
	//		if (gem->containsPoint(xClick, yClick)) {
	//			gem->collected = true;
	//			player->availableResources += gem->value;
	//		}
	//	}
	//	mouseClick = false;
	//}

	// Disparar
	if (controlShoot) {
		Projectile* newProjectile = player->shoot();
		if (newProjectile != nullptr) {
			projectiles.push_back(newProjectile);
			space->addDynamicActor(newProjectile);
		}
	}
	// Eje X
	if (controlMoveX > 0) {
		player->moveX(1);
	}
	else if (controlMoveX < 0) {
		player->moveX(-1);
	}
	else {
		player->moveX(0);
	}

	// Eje Y
	if (controlMoveY > 0) {

	}
	else if (controlMoveY < 0) {
		player->jump();
	}
	else {

	}
}

void GameLayer::keysToControls(SDL_Event event) {
	if (event.type == SDL_KEYDOWN) { // Tecla pulsada
		int code = event.key.keysym.sym;
		switch (code) {
		case SDLK_ESCAPE: // Tecla Esc
			game->loopActive = false;
			break;
		case SDLK_1: // Tecla 1
			game->scale();
			break;
		case SDLK_d: // derecha
			controlMoveX = 1;
			break;
		case SDLK_a: // izquierda
			controlMoveX = -1;
			break;
		case SDLK_w: // arriba
			controlMoveY = -1;
			break;
		case SDLK_s: // abajo
			controlMoveY = 1;
			break;
		case SDLK_SPACE: // disparar
			controlShoot = true;
			break;
		}
	}

	if (event.type == SDL_KEYUP) { // Tecla levantada
		int code = event.key.keysym.sym;
		switch (code) {
		case SDLK_d: // derecha
			if (controlMoveX == 1) {
				controlMoveX = 0;
			}
			break;
		case SDLK_a: // izquierda
			if (controlMoveX == -1) {
				controlMoveX = 0;
			}
			break;
		case SDLK_w: // arriba
			if (controlMoveY == -1) {
				controlMoveY = 0;
			}
			break;
		case SDLK_s: // abajo
			if (controlMoveY == 1) {
				controlMoveY = 0;
			}
			break;
		case SDLK_SPACE: // disparar
			controlShoot = false;
			break;
		}
	}

}

void GameLayer::mouseToControls(SDL_Event event) {
	// Modificaci�n de coordenadas por posible escalado
	float motionX = event.motion.x / game->scaleLower;
	float motionY = event.motion.y / game->scaleLower;

	this->xClick = motionX;
	this->yClick = motionY;

	this->mouseX = motionX;
	this->mouseY = motionY;

	// Cada vez que el usuario hace click
	if (event.type == SDL_MOUSEBUTTONDOWN) {
		//controlContinue = true;
		this->mouseClick = true;
		this->mouseReleased = false;
		this->mouseHold = true;
		/*for (auto const& ct : this->constructionTiles) {
			if (ct->containsPoint(motionX, motionY)) {
				this->controlConstruct = true;
				this->clickedCT = ct;
			}
		}*/
		
		/*	if (buttonShoot->containsPoint(motionX, motionY)) {
				controlShoot = true;
			}
			if (buttonJump->containsPoint(motionX, motionY)) {
				controlMoveY = -1;
			}*/
	}
	// Cada vez que se mueve
	if (event.type == SDL_MOUSEMOTION) {
		this->mouseClick = false;
		this->mouseReleased = false;
		/*for (auto const& ct : this->constructionTiles) {
			if (ct->containsPoint(motionX, motionY)) {
				this->controlConstruct = false;
				this->clickedCT = nullptr;
			}
		}*/
		//if (!buttonShoot->containsPoint(motionX, motionY)) { // Rat�n se mueve fuera del bot�n de disparo
		//	controlShoot = false;
		//}
		//if (!buttonJump->containsPoint(motionX, motionY)) {
		//	controlMoveY = 0;
		//}
	}

	// Cada vez que se levanta el click
	if (event.type == SDL_MOUSEBUTTONUP) {
		this->mouseClick = false;
		this->mouseReleased = true;
		this->mouseHold = false;
		//if (buttonShoot->containsPoint(motionX, motionY)) {
		//	controlShoot = false;
		//}
		//if (buttonJump->containsPoint(motionX, motionY)) {
		//	controlMoveY = 0;
		//}
	}
}



void GameLayer::draw() {

	background->draw();


	for (auto const& pathTile : pathTiles) {
		pathTile->draw();
	}

	// Dibujamos al jugador
	//player->draw(scrollX, scrollY);

	// Dibujamos los enemigos
	for (auto const& enemy : enemies) {
		enemy->draw();
	}


	// Dibujamos los proyectiles
	for (auto const& projectile : projectiles) {
		projectile->draw();
	}

	// Dibujamos las torres
	for (auto const& pair : towers) {
		pair.second->draw();
	}

	// Dibujar construction tiles
	for (auto const& ct : this->constructionManager->constructionTiles) {
		ct->draw();
	}


	// Dibujamos las torretas
	for (auto const& turret : this->constructionManager->turrets) {
		turret->draw();
	}

	// Dibujar recolectables
	for (auto const& gem : gems) {
		gem->draw();
	}

	// Dibujar UI con los items de las torretas
	this->shopManager->draw();

	this->uiRecursos->draw();
	this->uiLeftEnemies->draw();

	// Torreta seleccionada con el mouse
	if (this->selectedTurret != nullptr)
		this->selectedTurret->draw();


	//textPoints->draw();
	//backgroundPoints->draw();
	// HUD
	if (game->input == GameInputType::MOUSE) { // Dibujar el HUD solo si el tipo de entrada es el mouse
		//buttonJump->draw(); // NO TIENEN SCROLL, POSISICI�N FIJA
		//buttonShoot->draw();
	}

	if (pause) {
		message->draw();
	}
	

	SDL_RenderPresent(game->renderer); // Renderiza el juego
}



// M�todos privados
// **********************************************************************************


//void GameLayer::constructTurret(ConstructionTile* ct) {
//	if (!ct->occupied) { // Ocupada?
//		int x = (int)(ct->x / TILE_WIDTH) * TILE_WIDTH + TILE_WIDTH / 2;
//		int y = (int)(ct->y / TILE_HEIGHT) * TILE_HEIGHT + TILE_HEIGHT / 2;
//		Turret* newTurret = new Turret("res/cannon1.png", x, y, 55, 14, game);
//		this->turrets.push_back(newTurret);
//
//		cout << "Nueva torreta en x: " << x << " y: " << y << endl;
//		ct->occupied = true;
//
//	}
//	else {
//		cout << "Ya hay una torreta construida en ese lugar" << endl;
//	}
//}


void GameLayer::loadEntities() {
	this->pathTiles = mapManager->getPathTiles();
	this->pathManager = mapManager->getPathManager();
	this->constructionManager = mapManager->getConstructionManager();
	this->constructionManager->shopManager = this->shopManager;
	this->mapHeight = mapManager->getMapHeight();
	this->mapWidth = mapManager->getMapWidht();
	this->enemyGenerator = mapManager->getEnemyGenerator();
	this->towers = mapManager->getTowers();
	this->hordes = mapManager->getHordes();
}

bool GameLayer::hordeHasFinished() {
	return this->currentHorde != nullptr &&
		(this->currentHorde->totalNumberOfEnemies == player->killedEnemiesInActualHorde
			|| 
			(this->enemyGenerator->allGenerated && this->enemies.empty()));
}

//
//void GameLayer::addResourceCollectable() {
//	this->ticksUntilNextResourcesSpawn--;
//
//	if (this->ticksUntilNextResourcesSpawn <= 0) {
//		float rX = rand() % (770 - 30 + 1) + 30;
//		float rY = rand() % (570 - 30 + 1) + 30;
//		this->randomResources.push_back(new Resources(rX, rY, game));
//		this->ticksUntilNextResourcesSpawn = RESOURCES_SPAWN_FREQUENCY;
//	}
//}

Horde* GameLayer::getNextHorde() {
	if (!this->hordes.empty()) {
		Horde* next = this->hordes.front();
		this->hordes.pop();
		return next;
	}
	return nullptr;
}


void markTowerForDelete(Tower* tower, list<Tower*>& deleteList) {
	bool inList = std::find(deleteList.begin(),
		deleteList.end(),
		tower) != deleteList.end();
	if (!inList) {
		deleteList.push_back(tower);
	}
}

void markEnemyForDelete(Enemy* enemy, list<Enemy*>& deleteList) {
	bool inList = std::find(deleteList.begin(),
		deleteList.end(),
		enemy) != deleteList.end();
	if (!inList) {
		deleteList.push_back(enemy);
	}
}

void markProjectileForDelete(Projectile* projectile, list<Projectile*>& deleteList) {
	bool inList = std::find(deleteList.begin(),
		deleteList.end(),
		projectile) != deleteList.end();
	if (!inList) {
		deleteList.push_back(projectile);
	}
}


void markTileForDelete(Tile* tile, list<Tile*>& deleteList) {
	bool inList = std::find(deleteList.begin(),
		deleteList.end(),
		tile) != deleteList.end();
	if (!inList) {
		deleteList.push_back(tile);
	}
}

void markGemForDelete(Gem* gem, list<Gem*>& deleteList) {
	bool inList = std::find(deleteList.begin(),
		deleteList.end(),
		gem) != deleteList.end();
	if (!inList) {
		deleteList.push_back(gem);
	}
}


//
//void GameLayer::addNewEnemy() {
//	newEnemyTime--;
//	if (newEnemyTime <= 0) {
//		for (int i = 0; i < (killedEnemies / ENEMY_SPAWN_FREQUENCY) + 1; i++) {
//			cout << "New enemy spawned" << endl;
//			// Random position
//			int rX = (rand() % (600 - 500)) + 1 + 500;
//			int rY = (rand() % (300 - 60)) + 1 + 60;
//			enemies.push_back(new Enemy(rX, rY, 2, game));
//		}
//		newEnemyTime = ENEMY_SPAWN_TIME;
//	}
//}

void GameLayer::destroyEnemies() {
	for (auto const& enemy : enemies) {
		delete enemy;
	}
}

void GameLayer::destroyProjectiles() {
	for (auto const& projectile : projectiles) {
		delete projectile;
	}
}

