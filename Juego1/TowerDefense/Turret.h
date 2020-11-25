#pragma once

#include <list>
#include <math.h>

#include "Actor.h"
#include "Projectile.h"
#include "Enemy.h"


/// <summary>
/// Clase que hereda de Actor y que modela una torreta que
/// se puede construir en un ConstructionTile.
/// </summary>
class Turret : public Actor
{
public:
	Turret(string filename, float x, float y, 
		float width, float height, Game* game);
	Projectile* shoot();
	void update(list<Enemy*>& enemies);

	// Referencia al enemigo m�s cercano que es objetivo actual de disparo.
	Enemy* currentTarget;

	// Cadencia de disparo
	int shootCadency;
	int ticksUntilNextShoot;

	// �rea de detecci�n de enemigos (Indica el n� de tiles en el eje X
	// y en el eje Y que puede escanear la torreta para detectar a un enemigo.
	int xDetectionRange;
	int yDetectionRange;



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

