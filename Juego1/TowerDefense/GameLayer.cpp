#include "GameLayer.h"


void markEnemyForDelete(Enemy* enemy, list<Enemy*>& deleteList);
void markProjectileForDelete(Projectile* projectile, list<Projectile*>& deleteList);
void markTileForDelete(Tile* tile, list<Tile*>& deleteList);
void markTowerForDelete(Tower* tower, list<Tower*>& deleteList);
void markGemForDelete(Gem* gem, list<Gem*>& deleteList);
void markPowerUpForDelete(PowerUp* powerUp, list<PowerUp*>& deleteList);


GameLayer::GameLayer(Game* game)
	: Layer(game) { // Se hace una llamada al constructor del padre

	pause = false;
	message = new Actor("res/mensaje_como_jugar.png", WIDTH*0.5, HEIGHT*0.5,
		WIDTH, HEIGHT, game);
	init();
}

void GameLayer::init() {

	// Destruir posibles objetos existentes
	delete player;
	destroyEnemies();
	destroyProjectiles();
	destroyGems();
	destroyTowers();

	background = new Background("res/grass.jpg", WIDTH * 0.5, HEIGHT * 0.5, game);

	// Map Manager
	mapManager = new MapManager(game);

	// Collision engine
	collisionEngine = new CollisionEngine();

	// Enemigos
	enemies.clear(); // Vaciar la lista de enemigos, por si se reinicia el juego

	// Proyectiles
	projectiles.clear();

	// Gemas
	gems.clear();

	// Torres
	towers.clear();


	// Semilla aleatoria para generar números aleatorios
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
	uiRecursos = new UITextIcon(0.85 * WIDTH, 0.04 * HEIGHT, 29, 41, 50, color1, "res/gemsIcon.png", to_string(PLAYER_INITIAL_RESOURCES), game);
	uiLeftEnemies = new UITextIcon(0.75 * WIDTH, 0.04 * HEIGHT, 32, 32, 38, color1, "res/leftEnemiesIcon.png", "0", game);

	player = new Player(0, 0, game);

	// Gestor de compra
	this->shopManager = new ShopManager(player, game);

	// Carga del siguiente mapa
	mapManager->loadMap(getNextMap());
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
	this->powerUpGenerator = new PowerUpGenerator(game);
	this->powerUpInventory = new PowerUpInventory(game);

}


/**
* Método encargado de actualizar todos los elementos del juego.
**/
void GameLayer::update() {

	list<Enemy*> deleteEnemies; // Enemigos a eliminar
	list<Projectile*> deleteProjectiles; // Proyectiles a eliminar
	list<Tower*> deleteTowers; // Torres a eliminar
	list<Gem*> deleteGems; // Gemas recolectables a eliminar
	list<PowerUp*> deletePowerUps; // PowerUps a eliminar

	if (pause) {
		return;
	}

	// Si se han superado todas las rondas
	if (checkWin()) {
		message = new Actor("res/mensaje_ganar.png", WIDTH*0.5, HEIGHT*0.5, WIDTH, HEIGHT, game);
		pause = true;
		return;
	}

	if (this->towers.empty()) { //  Todas las torres destruidas
		message = new Actor("res/mensaje_perder.png", WIDTH*0.5, HEIGHT*0.5, WIDTH, HEIGHT, game);
		pause = true;
		this->init();
		return;
	}

	// Actualizar el motor de colisiones
	collisionEngine->update();

	// Actualizar generador de enemigos
	Enemy* newEnemy = this->enemyGenerator->createEnemy();
	if (newEnemy != nullptr) enemies.push_back(newEnemy);
	

	// Actualizamos los enemigos
	for (auto const& enemy : enemies) {
		pathManager->update(enemy); // Actualizar trayectoria del enemigo
		enemy->update(); // Actualizar estado del enemigo.
		// Enemigo a la izquierda de la pantalla
		if (enemy->x + enemy->width / 2 <= 0) {
			markEnemyForDelete(enemy, deleteEnemies);
		}
		else if (enemy->state == Enemy::EnemyState::DEAD) { // Enemigo está muerto -> eliminarlo
			markEnemyForDelete(enemy, deleteEnemies);
		}
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
		// Si la torre está destruida entonces se elimina
		if (pair.second->state == Tower::TowerState::DESTROYED) {
			markTowerForDelete(pair.second, deleteTowers);
		}
	}

	// Enemigos restantes
	if (this->currentHorde != nullptr) // Actualizar el nº de enemigos restantes
		leftEnemies = this->currentHorde->totalNumberOfEnemies - this->player->killedEnemiesInActualHorde;

	// Actualizar hordas
	if (this->currentHorde != nullptr) { // Aún no se han terminado las hordas...
		if (this->hordeHasFinished()) { // Horda finalizada
			this->currentHorde = getNextHorde();
			this->player->killedEnemiesInActualHorde = 0;
			if (this->currentHorde != nullptr) {
				this->enemyGenerator->setNextHorde(this->currentHorde, HORDE_DELAY);
				this->leftEnemies = this->currentHorde->totalNumberOfEnemies;
			}
		}
	}

	// Actualizar recolectables
	Gem* newGem = this->gemGenerator->createGem();
	if (newGem != nullptr)
		gems.push_back(newGem);

	for (auto const& gem : gems) {
		gem->update();
		if (gem->ticksAlive <= 0 // Se agotó su tiempo de vida
			|| gem->collected) { // o ya ha sido recolectada
			markGemForDelete(gem, deleteGems);
		}
	}

	// Actualizar generador de powerUps
	PowerUp* pwu = this->powerUpGenerator->createPowerUp();
	if (pwu != nullptr) this->powerUps.push_back(pwu);

	for (auto const& powerUp : powerUps) {
		powerUp->update();
		if (powerUp->collected || powerUp->ticksAlive <= 0)
			markPowerUpForDelete(powerUp, deletePowerUps);
	}

	// Actualizar UI
	this->uiRecursos->text->content = to_string(this->player->availableResources);
	this->uiLeftEnemies->text->content = to_string(this->leftEnemies);


	// Eliminar torres destruidas
	for (auto const& tower : deleteTowers) {
		towers.erase(tower->pathId);
		delete tower;
	}
	deleteTowers.clear();

	// Eliminamos los proyectiles y enemigos necesarios
	for (auto const& delEnemy : deleteEnemies) {
		enemies.remove(delEnemy);
		delete delEnemy; // Se destruye el enemigo.
	}
	deleteEnemies.clear();

	for (auto const& delProjectile : deleteProjectiles) {
		projectiles.remove(delProjectile);
		delete delProjectile; // Se destruye el proyectil.
	}
	deleteProjectiles.clear();

	for (auto const& delGem : deleteGems) {
		gems.remove(delGem);
		delete delGem;
	}
	deleteGems.clear();

	for (auto const& delPowerUp : deletePowerUps) {
		powerUps.remove(delPowerUp);
		delete delPowerUp;
	}
	deletePowerUps.clear();
}


void GameLayer::processControls() {
	// obtener controles
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		// Cambio automático del input
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

	// Eventos de ratón
	if (mouseClick) {
		cout << "Mouse clicked!" << endl;
		// Si el juego estaba en pausa, continuar
		if (pause) {
			this->init();
			pause = false;
		}

		// Coger un powerUp del inventario de powerUps
		UIPowerUp* slot = this->powerUpInventory->getSlot(mouseX, mouseY);
		if (slot != nullptr && !slot->empty()) {
			this->selectedPowerUp = slot->powerUp;
			slot->clear();
		}

		// Comprobar la compra de torretas
		this->selectedTurret = this->shopManager->purchase(mouseX, mouseY);
		
		// Comprobar la recolección de gemas
		for (auto const& gem : gems) {
			if (gem->containsPoint(xClick, yClick)) {
				gem->collected = true;
				player->availableResources += gem->value;
			}
		}

		// Comprobar la recolección de powerUps
		for (auto const& pwu : powerUps) {
			if (pwu->containsPoint(xClick, yClick) && !this->powerUpInventory->isFull()) {
				pwu->collected = true;
				this->powerUpInventory->addPowerUp(pwu->clone()); // Crear un clone del powerUp y añadirlo al inventario
			}
		}

		// Comprobar la recolección de powerups
		mouseClick = false;
	}
		

	if (mouseReleased) {
		cout << "Mouse released!" << endl;
		// Torreta
		this->constructionManager->construct(mouseX, mouseY, this->selectedTurret);
		this->selectedTurret = nullptr;
		this->shopManager->clearPurchase();

		// PowerUp
		// Comprobar si se suelta encima de alguna torre
		if (this->selectedPowerUp != nullptr) {
			for (auto const& pair : towers) {
				if (pair.second->containsPoint(mouseX, mouseY)) {
					this->selectedPowerUp->effect(pair.second);
				}
			}
			if (!this->selectedPowerUp->used) { // Si no se ha soltado encima de una torre, devolverlo al slot
				this->powerUpInventory->addPowerUp(this->selectedPowerUp);
			}
			this->selectedPowerUp = nullptr;
		}
		

		mouseReleased = false;
	}
		
	if (mouseHold) {
		cout << "Mouse hold!" << endl;
		if (this->selectedTurret != nullptr) {
			this->selectedTurret->x = this->mouseX;
			this->selectedTurret->y = this->mouseY;
		}

		if (this->selectedPowerUp != nullptr) {
			this->selectedPowerUp->x = this->mouseX;
			this->selectedPowerUp->y = this->mouseY;
		}
	}
		

	// Se ha hecho click con el ratón
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
	//if (controlShoot) {
	//	Projectile* newProjectile = player->shoot();
	//	if (newProjectile != nullptr) {
	//		projectiles.push_back(newProjectile);
	//	}
	//}
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
	// Modificación de coordenadas por posible escalado
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
		//if (!buttonShoot->containsPoint(motionX, motionY)) { // Ratón se mueve fuera del botón de disparo
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

	if (!pause) {
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

		for (auto const& powerUp : powerUps) {
			powerUp->draw();
		}
		

		// Dibujar UI con los items de las torretas
		this->shopManager->draw();
		this->uiRecursos->draw();
		this->uiLeftEnemies->draw();
		this->powerUpInventory->draw();

		// Torreta seleccionada con el mouse
		if (this->selectedTurret != nullptr)
			this->selectedTurret->draw();
		// PowerUp seleccionado con el mouse
		if (this->selectedPowerUp != nullptr) {
			this->selectedPowerUp->draw();
		}

		//textPoints->draw();
		//backgroundPoints->draw();
		// HUD
		if (game->input == GameInputType::MOUSE) { // Dibujar el HUD solo si el tipo de entrada es el mouse
			//buttonJump->draw(); // NO TIENEN SCROLL, POSISICIÓN FIJA
			//buttonShoot->draw();
		}
	}
	else {
		this->message->draw();
	}
	
	
	SDL_RenderPresent(game->renderer); // Renderiza el juego
}



// Métodos privados
// **********************************************************************************


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

Horde* GameLayer::getNextHorde() {
	if (!this->hordes.empty()) {
		Horde* next = this->hordes.front();
		this->hordes.pop();
		return next;
	}
	return nullptr;
}


bool GameLayer::checkWin() {
	return this->hordes.empty() && this->leftEnemies == 0;
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

void markPowerUpForDelete(PowerUp* powerUp, list<PowerUp*>& deleteList) {
	bool inList = std::find(deleteList.begin(),
		deleteList.end(),
		powerUp) != deleteList.end();
	if (!inList) {
		deleteList.push_back(powerUp);
	}
}

string GameLayer::getNextMap()
{
	if (maps.empty())
		initMaps();
	string nextMap = maps.front();
	maps.pop();
	return nextMap;
}

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

void GameLayer::destroyGems()
{
	for (auto const& gem : gems) {
		delete gem;
	}
}

void GameLayer::destroyTowers()
{
	for (auto const& tower : towers) {
		delete tower.second;
	}
}


void GameLayer::initMaps() {
	this->maps.push("res/mapa-1.txt");
	this->maps.push("res/mapa-2.txt");
}
