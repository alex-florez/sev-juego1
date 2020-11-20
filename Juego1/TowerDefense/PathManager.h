#pragma once

#include "Path.h"
#include "Actor.h"
#include "Pawn.h"

#include <map>

/// <summary>
/// Clase que se encarga de la gesti�n de trayectorias que
/// deben seguir los actores.
/// </summary>
class PathManager
{
public:
	
	PathManager();

	/// <summary>
	/// A�ade una nueva trayectoria al mapa, con id
	/// pasado como par�metro.
	/// </summary>
	/// <param name="id">id de la trayectoria</param>
	/// <param name="path">objeto que modela la trayectoria</param>
	void addPath(int id, Path* path);

	/// <summary>
	/// Dado un id, devueelve la trayectoria asociada
	/// a dicho id.
	/// </summary>
	/// <param name="id">id de la trayectoria</param>
	/// <returns>objeto que representa la trayectoria</returns>
	Path* getPath(int id);

	/// <summary>
	/// M�todo encargado de actualizar la velocidad del actor de acuerdo
	/// a la trayectoria que este debe se seguir.
	/// </summary>
	/// <param name="actor"></param>
	void update(Pawn* pawn);

	/// <summary>
	/// A�ade el punto pasado como par�metro, a la trayectoria
	/// de id indicado.
	/// </summary>
	/// <param name="pathId">Id de la trayectoria</param>
	/// <param name="point">Punto</param>
	void addPointToPath(int pathId, Point* point);


private:
	map<int, Path*> paths;

};

