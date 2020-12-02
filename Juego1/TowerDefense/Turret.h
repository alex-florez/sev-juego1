#pragma once

#include <list>
#include <math.h>

#include "Actor.h"
#include "Enemy.h"
#include "Animation.h"
#include "ProjectileFactory.h"
#include "SoundEffect.h"



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
	/// M�todo encargado de UPGRADEAR esta torreta.
	/// </summary>
	virtual void upgrade() = 0;

	// Referencia al enemigo m�s cercano que es objetivo actual de disparo.
	Enemy* currentTarget;

	// Id de la torreta
	int id;

	// n� de enemigos eliminados por esta torreta.
	int killedEnemies;
	int killedEnemiesForUpgrade; // Indica el n� de enemigos que debe eliminar esta torreta para poder ser mejorada.

	// Cadencia de disparo
	int shootCadency;
	int ticksUntilNextShoot;

	// �rea de detecci�n de enemigos (Indica el n� de tiles en el eje X
	// y en el eje Y que puede escanear la torreta para detectar a un enemigo.
	int xDetectionRange;
	int yDetectionRange;
	int cost; // Coste de la torreta

	bool enabled; // Indica si la torreta est� activada
	bool canBeUpgraded; // Indica si la torreta est� lista para ser mejorada. 
	TurretState state; // Estado de la torreta

	// Animaciones
	Animation* constructionAnimation; // Animaci�n de construcci�n
	Animation* canBeUpgradedAnimation; // Animaci�n de que la torreta puede ser mejorada

	ProjectileFactory* projectileFactory; // Factor�a de proyectiles

	// Sonidos
	SoundEffect* shotSound;

	// Valores offset de "y" de los dos ca�ones de la torreta si est� mejorada
	float upgradedYCannonOffsets[2];
	// Offset en el eje "y" para situar los proyectiles en la punta del ca��n.
	float yCannonOffset;

private:

	/// <summary>
	/// Comprueba si el enemigo pasado como par�metro se encuentra 
	/// o no en el �rea de efecto de la torreta.
	/// </summary>
	/// <param name="enemy">Referencia al enemigo</param>
	/// <returns>true si est� dentro del �rea</returns>
	bool isInArea(Enemy* enemy);

	/// <summary>
	/// Se encarga de escanear la lista de enemigos
	/// pasada como par�metro para ver si alguno est� dentro
	/// del �rea de efecto de esta torreta. Adem�s si hay varios,
	/// selecciona el m�s cercano a la torreta.
	/// </summary>
	/// <param name="enemies"></param>
	void scan(list<Enemy*>& enemies);

	/// <summary>
	/// Devuelve la distancia vectorial entre los dos puntos
	/// cuyas componentes se pasan como par�metro.
	/// </summary>
	/// <param name="x1"></param>
	/// <param name="y1"></param>
	/// <param name="x2"></param>
	/// <param name="y2"></param>
	/// <returns></returns>
	float distance(float x1, float y1, float x2, float y2);

	/// <summary>
	/// M�todo que devuelve el �ngulo de rotaci�n en grados que 
	/// debe de rotar esta torreta para apuntar al enemigo objetivo.
	/// </summary>
	/// <returns></returns>
	float calculateAngleOfRotation();
};

