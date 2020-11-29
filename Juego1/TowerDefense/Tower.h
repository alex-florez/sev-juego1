#pragma once

#include "Actor.h"
#include "Animation.h"
#include "UITextIcon.h"
#include "UIRepairIcon.h"

#define TOWER_REPAIR_COST 600
#define TOWER_INITIAL_HEALTH 100

/// <summary>
/// Clase que modela una torre que se debe defender
/// de los enemigos, para evitar ser destruida.
/// </summary>
class Tower : public Actor
{
public:
	Tower(string filename, float x, float y, Game* game);
	void draw() override;
	void update();
	void repair();
	void hit(float damage);

	int health;
	int pathId;
	bool applyingPowerUp;
	UITextIcon* uiHealth; // Icono de la UI que muestra una etiqueta encima de la torre con su salud actual.
	enum class TowerState {ALIVE, EXPLODING, DESTROYED, REPAIRED} state;
	Animation* explotionAnim; // Animación de explosión
	Animation* powerUpEffectAnimation; // Animación de aplicación de mejora
	Actor* destroyedGround;
	UIRepairIcon* repairIcon;

};

