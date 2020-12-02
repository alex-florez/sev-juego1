#pragma once

#include <list>
#include <math.h>

#include "Actor.h"
#include "Enemy.h"
#include "Animation.h"
#include "ProjectileFactory.h"
#include "SoundEffect.h"
#include "UITextIcon.h"



/// <summary>
/// Clase que hereda de Actor y que modela una torreta que
/// se puede construir en un ConstructionTile.
/// </summary>
class Turret : public Actor
{
public:
	/// <summary>
	/// PURCHASED: Se acaba de comprar la torreta
	/// BUILDING: Se esta colocando
	/// BUILT: Ya se ha colocado
	/// UPGRADED: la torreta se ha mejorado
	/// </summary>
	enum class TurretState {
		PURCHASED, BUILDING, BUILT, UPGRADED
	};

	Turret(string filename, float x, float y, 
		float width, float height, int cost, Game* game);
	list<Projectile*> shoot();
	void update(list<Enemy*>& enemies);
	void draw() override;


	/// <summary>
	/// Método encargado de UPGRADEAR esta torreta.
	/// </summary>
	virtual void upgrade() = 0;

	// Referencia al enemigo más cercano que es objetivo actual de disparo.
	Enemy* currentTarget;

	// Id de la torreta
	int id;

	// nº de enemigos eliminados por esta torreta.
	int killedEnemies;
	int killedEnemiesForUpgrade; // Indica el nº de enemigos que debe eliminar esta torreta para poder ser mejorada.

	// Cadencia de disparo
	int shootCadency;
	int ticksUntilNextShoot;

	// Área de detección de enemigos (Indica el nº de tiles en el eje X
	// y en el eje Y que puede escanear la torreta para detectar a un enemigo.
	int xDetectionRange;
	int yDetectionRange;
	int cost; // Coste de la torreta

	bool enabled; // Indica si la torreta está activada
	bool canBeUpgraded; // Indica si la torreta está lista para ser mejorada.
	bool upgradeHasFinished; // Indica si se ha terminado de Upgradear.
	TurretState state; // Estado de la torreta

	// Animaciones
	Animation* constructionAnimation; // Animación de construcción
	Animation* canBeUpgradedAnimation; // Animación de que la torreta puede ser mejorada
	Animation* upgradeAnimation; // Animación de UPGRADE

	ProjectileFactory* projectileFactory; // Factoría de proyectiles

	// Icono de interfaz situado sobre la torreta indicando el precio de upgrade
	UITextIcon* uiUpgradeCost;
	int upgradeCost;

	// Sonidos
	SoundEffect* shotSound;

	// Valores offset de "y" de los dos cañones de la torreta si está mejorada
	float upgradedYCannonOffsets[2];
	// Offset en el eje "y" para situar los proyectiles en la punta del cañón.
	float yCannonOffset;

private:

	/// <summary>
	/// Comprueba si el enemigo pasado como parámetro se encuentra 
	/// o no en el área de efecto de la torreta.
	/// </summary>
	/// <param name="enemy">Referencia al enemigo</param>
	/// <returns>true si está dentro del área</returns>
	bool isInArea(Enemy* enemy);

	/// <summary>
	/// Se encarga de escanear la lista de enemigos
	/// pasada como parámetro para ver si alguno está dentro
	/// del área de efecto de esta torreta. Además si hay varios,
	/// selecciona el más cercano a la torreta.
	/// </summary>
	/// <param name="enemies"></param>
	void scan(list<Enemy*>& enemies);

	/// <summary>
	/// Devuelve la distancia vectorial entre los dos puntos
	/// cuyas componentes se pasan como parámetro.
	/// </summary>
	/// <param name="x1"></param>
	/// <param name="y1"></param>
	/// <param name="x2"></param>
	/// <param name="y2"></param>
	/// <returns></returns>
	float distance(float x1, float y1, float x2, float y2);

	/// <summary>
	/// Método que devuelve el ángulo de rotación en grados que 
	/// debe de rotar esta torreta para apuntar al enemigo objetivo.
	/// </summary>
	/// <returns></returns>
	float calculateAngleOfRotation();
};

