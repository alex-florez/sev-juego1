#pragma once
#include "Enemy.h"

#define EXECUTIONER_KILL_RESOURCES 150

class Executioner : public Enemy
{
public:
	Executioner(float x, float y, float speed, Game* game);
};

