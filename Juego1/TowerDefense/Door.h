#pragma once

#include "Actor.h"
#include "Player.h"

class Door : public Actor
{
public:
	Door(char id, float x, float y, Game* game);

	void teleport(Player* player); // M�todo para teletransportar al jugador


	char id; // Id de la puerta
	float destinyX; // X de la puerta destino
	float destinyY; // Y de la puerta destino
};

