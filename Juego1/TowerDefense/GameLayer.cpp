#include "GameLayer.h"


void markEnemyForDelete(Enemy* enemy, list<Enemy*>& deleteList);
void markProjectileForDelete(Projectile* projectile, list<Projectile*>& deleteList);
void markTowerForDelete(Tower* tower, list<Tower*>& deleteList);
void markGemForDelete(Gem* gem, list<Gem*>& deleteList);
void markPowerUpForDelete(PowerUp* powerUp, list<PowerUp*>& deleteList);


GameLayer::GameLayer(Game* game)
	: Layer(game) { // Se hace una llamada al constructor del padre

	pause = false;
	reset = false;
	message = new Actor("res/mensaje_como_jugar.png", WIDTH*0.5, HEIGHT*0.5, WIDTH, HEIGHT, game);
	init();
}

void GameLayer::init() {
	// Sonido
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096)) {
		cout << "Error: " << Mix_GetError() << endl;
	}

	// Destruir posibles objetos existentes
	delete player;
	destroyEnemies();
	destroyProjectiles();
	destroyGems();
	destroyPowerUps();

	background = new Background("res/grass.jpg", WIDTH * 0.5, HEIGHT * 0.5, game); // Fondo										  
	mapManager = new MapManager(game);  // Map Manager
	collisionEngine = new CollisionEngine(); // Collision engine
	enemies.clear(); // Enemigos
	projectiles.clear(); // Proyectiles
	gems.clear(); // Gemas
	powerUps.clear(); // PowerUps
	srand(SDL_GetTicks()); // Semilla aleatoria para generar números aleatorios

	// Eventos de ratón
	this->mouseClick = false;
	this->mouseHold = false;
	this->mouseReleased = false;

	this->selectedTurret = nullptr; // Torreta seleccionada con el ratón
	backgroundMusic = Mix_LoadMUS("res/musica_ambiente.mp3"); // Audio de fondo
	upgradeSound = new SoundEffect("res/sounds/upgrade.wav");

	player = new Player(0, 0, game); // Jugador
	this->shopManager = new ShopManager(player, game); 	// Gestor de compra

	// Carga del siguiente mapa
	mapManager->loadMap(getNextMap());
	loadEntities();

	// nº máximo de enemigos que se pueden colar a la izquierda.
	this->maxInfiltratedEnemies = (int) (mapManager->getTotalNumberOfEnemies() / 2);
	this->infiltratedEnemies = 0;

	// inicializar UI
	RGB* color1 = new RGB(255, 255, 23);
	uiRecursos = new UITextIcon(0.85 * WIDTH, 0.04 * HEIGHT, 29, 41, 50, color1, "res/gemsIcon.png", to_string(PLAYER_INITIAL_RESOURCES), game);
	uiLeftEnemies = new UITextIcon(0.75 * WIDTH, 0.04 * HEIGHT, 32, 32, 38, color1, "res/leftEnemiesIcon.png", "0", game);
	uiHordeCounter = new UIHordeCounter(0.5 * WIDTH, 0.04 * HEIGHT, game);
	uiInfiltratedEnemies = new UITextIcon(0.04 * WIDTH, 0.04 * HEIGHT, 32, 32, 38, color1, 
		"res/death.png", "0/" + to_string(this->maxInfiltratedEnemies), game);

	// inicializar el motor de colisiones
	this->collisionEngine->addTowers(&this->towerManager->towers);
	this->collisionEngine->addEnemies(&this->enemies);
	this->collisionEngine->addProjectiles(&this->projectiles);
	this->collisionEngine->addPlayer(player);
	this->collisionEngine->addTurrets(&this->constructionManager->turrets);

	// Horda inicial
	this->currentHorde = getNextHorde();
	this->enemyGenerator->setNextHorde(this->currentHorde, 0); // Establecer la ronda inicial al generador de enemigos
	this->leftEnemies = this->currentHorde->totalNumberOfEnemies; // Enemigos restantes

	this->gemGenerator = new GemGenerator(game); // Generador de gemas
	this->powerUpGenerator = new PowerUpGenerator(game); // Generador de PowerUps
	this->powerUpInventory = new PowerUpInventory(game); // Inventario de PowerUps

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

	// Si se han superado todas las rondas, pasar al siguiente mapa.
	if (checkWin()) {
		this->maps.pop(); // Popear el mapa actual
		message = new Actor("res/mensaje_ganar.png", WIDTH*0.5, HEIGHT*0.5, WIDTH, HEIGHT, game);
		pause = true;
		reset = true;
		return;
	}

	// Si se han destruido todas las torres o se han infiltrado demasiados enemigos... el jugador pierde
	if (checkLoose()) { 
		message = new Actor("res/mensaje_perder.png", WIDTH*0.5, HEIGHT*0.5, WIDTH, HEIGHT, game);
		pause = true;
		reset = true;
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
		if (enemy->infiltrated()) { // Enemigo a la izquierda de la pantalla (infiltrado)
			this->infiltratedEnemies++;
			markEnemyForDelete(enemy, deleteEnemies);
		}
		else if (enemy->state == Enemy::EnemyState::DEAD) { // Enemigo está muerto -> eliminarlo
			markEnemyForDelete(enemy, deleteEnemies);
		}
	}

	// Actualizar las torretas
	for (auto const& turret : this->constructionManager->turrets) {
		turret->update(this->enemies); // Escanear enemigos
		list<Projectile*> tProjectiles = turret->shoot(); // Realizar disparo
		for (auto const& p : tProjectiles) {
			projectiles.push_back(p);
		}
	}

	// Actualizar los proyectiles
	for (auto const& projectile : projectiles) {
		projectile->update();
		if (!projectile->isInRender() || projectile->destroyed) { // Proyectil fuera del render o destruido
			markProjectileForDelete(projectile, deleteProjectiles);
		}
	}

	// Actualizar torres
	for (auto const& pair : this->towerManager->towers) {
		pair.second->update();
		// Si la torre está destruida entonces se elimina y Eliminar del generador de enemigos el punto de aparición de esta trayectoria
		if (pair.second->state == Tower::TowerState::DESTROYED) {
			this->enemyGenerator->removeSpawnPoint(pair.second->pathId); 
		}
		else if (pair.second->state == Tower::TowerState::REPAIRED) { // Si se ha reparado...
			Point* start = this->pathManager->getPath(pair.second->pathId)->getStartingPoint();
			this->enemyGenerator->addSpawnPoint(pair.second->pathId, start); // Volver a añadir el spawn de los enemigos
			pair.second->state = Tower::TowerState::ALIVE;
		}
	}

	// Actualizar hordas
	if (this->hordeHasFinished()) { // Horda finalizada
		this->currentHorde = getNextHorde();
		this->player->killedEnemiesInActualHorde = 0;
		if (this->currentHorde != nullptr) {
			this->enemyGenerator->setNextHorde(this->currentHorde, HORDE_DELAY);
		}
	}

	// Actualizar enemigos restantes
	if (this->currentHorde != nullptr) // Actualizar el nº de enemigos restantes
		leftEnemies = this->currentHorde->totalNumberOfEnemies - this->player->killedEnemiesInActualHorde;
	

	// Actualizar recolectables
	Gem* newGem = this->gemGenerator->createGem();
	if (newGem != nullptr) gems.push_back(newGem);

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
	this->uiRecursos->text->content = to_string(this->player->availableResources); // Recursos
	this->uiLeftEnemies->text->content = to_string(this->leftEnemies); // Enemigos restantes
	if(this->currentHorde != nullptr)
		this->uiHordeCounter->hordeNumberTxt->content = to_string(this->currentHorde->id); // Horda actual
	this->uiInfiltratedEnemies->text->content = to_string(this->infiltratedEnemies) + "/" + to_string(this->maxInfiltratedEnemies);
	this->shopManager->updateTurretItems(player->availableResources);

	// Eliminar torres destruidas
	for (auto const& tower : deleteTowers) {
		this->towerManager->remove(tower->pathId);
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
			Mix_FreeMusic(backgroundMusic);
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
	// Eventos de ratón
	// ****************

	// Botón izquierdo del ratón pulsado
	if (mouseClick) {
		cout << "Mouse clicked!" << endl;
		if (pause) { // Si el juego estaba en pausa, continuar
			pause = false;
			if (reset) { // Comprobar si hay que resetear
				this->init();
				reset = false;
			}
		}
		
		// Comprobar si se ha hecho click en alguna torreta que esté lista para
		// ser UPGRADEDADA.
		for (auto const& turret : this->constructionManager->turrets) {
			if (turret->canBeUpgraded && turret->state != Turret::TurretState::UPGRADED
				&& turret->containsPoint(mouseX, mouseY)) {
				// Comprobar recursos del usuario
				if (player->availableResources >= turret->upgradeCost) {
					player->availableResources -= turret->upgradeCost;
					turret->upgrade();
					this->upgradeSound->play();
				}	
			}
		}

		// Reparar una torre
		Tower* clickedTower = this->towerManager->getTower(mouseX, mouseY);
		if (clickedTower != nullptr && clickedTower->state == Tower::TowerState::DESTROYED) {
			// Comprobar si hay recursos
			if (player->availableResources >= TOWER_REPAIR_COST) {
				this->player->availableResources -= TOWER_REPAIR_COST;
				clickedTower->repair(); // Reparar una torre
			}
		}

		// Coger un powerUp del inventario de powerUps
		UIPowerUp* slot = this->powerUpInventory->getSlot(mouseX, mouseY);
		if (slot != nullptr && !slot->empty()) {
			this->selectedPowerUp = slot->powerUp;
			slot->clear();
			slot->clickSound->play();
		}

		// Comprobar la compra de torretas
		this->selectedTurret = this->shopManager->purchase(mouseX, mouseY);
		
		// Comprobar la recolección de gemas
		for (auto const& gem : gems) {
			if (gem->containsPoint(mouseX, mouseY)) {
				gem->collected = true;
				gem->pickUpSound->play();
				player->availableResources += gem->value;
			}
		}

		// Comprobar la recolección de powerUps
		for (auto const& pwu : powerUps) {
			if (pwu->containsPoint(mouseX, mouseY) && !this->powerUpInventory->isFull()) {
				pwu->collected = true;
				pwu->pickUpSound->play();
				this->powerUpInventory->addPowerUp(pwu->clone()); // Crear un clone del powerUp y añadirlo al inventario
			}
		}

		// Comprobar la recolección de powerups
		mouseClick = false;
	}
		
	// Botón izquierdo del ratón suelto
	if (mouseReleased) {
		cout << "Mouse released!" << endl;
		// Torreta
		this->constructionManager->construct(mouseX, mouseY, this->selectedTurret);
		this->selectedTurret = nullptr;
		this->shopManager->clearPurchase();

		// Aplicar un powerUp a una torre
		if (this->selectedPowerUp != nullptr) {
			Tower* affectedTower = this->towerManager->getTower(mouseX, mouseY);
			if (affectedTower != nullptr) this->selectedPowerUp->effect(affectedTower);
			// Si no se ha podido usar el power UP
			if(!this->selectedPowerUp->used)
				this->powerUpInventory->addPowerUp(this->selectedPowerUp);
		}	
		this->selectedPowerUp = nullptr;
	
		mouseReleased = false;
	}
	
	// Botón izquierdo del ratón presionado
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

}

void GameLayer::keysToControls(SDL_Event event) {
	if (event.type == SDL_KEYDOWN) { // Tecla pulsada
		int code = event.key.keysym.sym;
		switch (code) {
		case SDLK_ESCAPE: // Tecla Esc
			game->loopActive = false;
			break;
		case SDLK_p: // Tecla P
			this->pauseGame();
			break;
		case SDLK_1: // Tecla 1
			game->scale();
			break;
		}
	}

}

void GameLayer::mouseToControls(SDL_Event event) {

	// Coordenadas del puntero del ratón
	this->mouseX = event.motion.x / game->scaleLower;
	this->mouseY = event.motion.y / game->scaleLower;

	// Cada vez que el usuario hace click
	if (event.type == SDL_MOUSEBUTTONDOWN) {
		//controlContinue = true;
		this->mouseClick = true;
		this->mouseReleased = false;
		this->mouseHold = true;
	}

	// Cada vez que se mueve
	if (event.type == SDL_MOUSEMOTION) {
		this->mouseClick = false;
		this->mouseReleased = false;
	}

	// Cada vez que se levanta el click
	if (event.type == SDL_MOUSEBUTTONUP) {
		this->mouseClick = false;
		this->mouseReleased = true;
		this->mouseHold = false;
	}
}



void GameLayer::draw() {

	if (!pause) {
		background->draw();

		// Dibujamos cada una de las trayectorias
		for (auto const& pathTile : pathTiles) {
			pathTile->draw();
		}

		// Dibujamos las torres
		this->towerManager->draw();

		// Dibujar construction tiles
		for (auto const& ct : this->constructionManager->constructionTiles) {
			ct->draw();
		}

		// Dibujamos los proyectiles
		for (auto const& projectile : projectiles) {
			projectile->draw();
		}

		// Dibujamos las torretas
		for (auto const& turret : this->constructionManager->turrets) {
			turret->draw();
		}

		// Dibujamos a los enemigos
		for (auto const& enemy : enemies) {
			enemy->draw();
		}

		// Dibujar recolectables
		for (auto const& gem : gems) { // Gemas
			gem->draw();
		}

		for (auto const& powerUp : powerUps) { // PowerUps
			powerUp->draw();
		}
		

		// Dibujar UI con los items de las torretas
		this->shopManager->draw();
		this->uiRecursos->draw();
		this->uiLeftEnemies->draw();
		this->uiHordeCounter->draw();
		this->uiInfiltratedEnemies->draw();
		this->powerUpInventory->draw();

		// Torreta seleccionada con el mouse
		if (this->selectedTurret != nullptr)
			this->selectedTurret->draw();
		// PowerUp seleccionado con el mouse
		if (this->selectedPowerUp != nullptr) {
			this->selectedPowerUp->draw();
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
	this->towerManager = mapManager->getTowerManager();
	this->hordes = mapManager->getHordes();
}

bool GameLayer::hordeHasFinished() {
	return this->enemyGenerator->allGenerated() && this->enemies.empty();
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
	return !this->towerManager->allDestroyed() // Alguna torre viva...
		&& this->enemyGenerator->allGenerated() // Todos los enemigos de la horda actual generados...
		&& this->enemies.empty() // No hay enemigos en el render...
		&& this->hordes.empty() // Ya no hay más hordas.
		&& this->infiltratedEnemies < this->maxInfiltratedEnemies; // Se han infiltrado menos enemigos que el máximo permitido.
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
	return maps.front();
}


void GameLayer::pauseGame()
{
	if (this->pause) this->pause = false;
	else {
		this->pause = true;
		this->message = new Actor("res/ComoJugar.png", WIDTH * 0.5, HEIGHT * 0.5, WIDTH, HEIGHT, game);
	}
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
	for (auto const& tower : this->towerManager->towers) {
		delete tower.second;
	}
}

void GameLayer::destroyPowerUps() {
	for (auto const& powerUp: powerUps) {
		delete powerUp;
	}
}


bool GameLayer::checkLoose()
{
	return this->towerManager->allDestroyed()
		|| this->infiltratedEnemies >= this->maxInfiltratedEnemies;
}

void GameLayer::initMaps() {
	this->maps.push("res/levels/mapa-1.txt");
	this->maps.push("res/levels/mapa-2.txt");
}
