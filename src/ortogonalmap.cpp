#include "agl/mapping/ortogonalmap.h"

AGL::IntVector2 AGL::OrtogonalMap::getAbsoluteSize()
{
	IntVector2 v(tileSize->x * size->x, tileSize->y * size->y);
	return v;
}

AGL::OrtogonalMap::OrtogonalMap(int tileWidth, int tileHeight, int tileXCount, int tileYCount, AGL::IntVector2 &screenSize) :
   Map(tileWidth, tileHeight, tileXCount, tileYCount, screenSize)
{

}

AGL::OrtogonalMap::OrtogonalMap(int tileWidth, int tileHeight, int tileXCount, int tileYCount, AGL::Camera* camera) : 
   Map(tileWidth, tileHeight, tileXCount, tileYCount, camera)
{

}

AGL::IntVector2 AGL::OrtogonalMap::getPosition(AGL::IntVector2 &screenPosition)
{
	IntVector2 v((screenPosition.x + camera->origin->x) / tileSize->x, (screenPosition.y + camera->origin->y) / tileSize->y);
	return v;
}

AGL::IntVector2 AGL::OrtogonalMap::getScreenPosition(AGL::IntVector2 &mapPosition)
{
	IntVector2 v(mapPosition.x * tileSize->x - camera->origin->x, mapPosition.y * tileSize->y - camera->origin->y);
   return v;
}

void AGL::OrtogonalMap::forEach(void (*drawMethod)(int, int, int, int))
{
	for (int j = 0; j < size->y; j++) 
		for (int i = 0; i < size->x; i++) 
			(*drawMethod)(i, j, tileSize->x * i - camera->origin->x, tileSize->y * j - camera->origin->y);
}

void AGL::OrtogonalMap::forEachVisible(void (*drawMethod)(int, int, int, int)) 
{
	if(camera->hasMoved()) setMapVisibleBounds();

	for (int j = minimumVisibleY; j <= maximumVisibleY; j++)
		for (int i = minimumVisibleX; i <= maximumVisibleX; i++)                 
			(*drawMethod)(i, j, i * tileSize->x - camera->origin->x, j * tileSize->y - camera->origin->y);
}

void AGL::OrtogonalMap::setMapVisibleBounds()
{
	minimumVisibleX = camera->origin->x / tileSize->x;
	minimumVisibleY = camera->origin->y / tileSize->y;
	maximumVisibleX = (camera->origin->x + camera->screenSize->x - 1) / tileSize->x;
	maximumVisibleY = (camera->origin->y + camera->screenSize->y - 1) / tileSize->y;

	if (minimumVisibleY < 0) minimumVisibleY = 0;
	else if (minimumVisibleY > size->y - 1) minimumVisibleY = size->y - 1;

	if (maximumVisibleY < 0) maximumVisibleY = 0;
	else if (maximumVisibleY > size->y - 1) maximumVisibleY = size->y - 1;

	if (minimumVisibleX < 0) minimumVisibleX = 0;
	else if (minimumVisibleX > size->x - 1) minimumVisibleX = size->x - 1;

	if (maximumVisibleX < 0) maximumVisibleX = 0;
	else if (maximumVisibleX > size->x - 1) maximumVisibleX = size->x - 1;
}

