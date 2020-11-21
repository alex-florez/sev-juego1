#pragma once

#include "Actor.h"
#include "Animation.h"
#include "UITextIcon.h"

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

	int health;
	int pathId;
	UITextIcon* uiHealth; // Icono de la UI que muestra una etiqueta encima de la torre con su salud actual.
	enum class TowerState {ALIVE, EXPLODING, DESTROYED} state;
	Animation* explotionAnim; // Animación de explosión

};

