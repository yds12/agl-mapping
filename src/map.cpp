#include "agl/mapping/map.h"

// Size of the tile
AGL::IntVector2 AGL::Map::getTileSize() 
{ 
	return *tileSize; 
}

// Size of the map in tiles
AGL::IntVector2 AGL::Map::getSize() 
{ 
	return *size; 
}

// Minimum visible X coordinate of the map in the screen
int AGL::Map::getMinimumVisibleX() 
{ 
	return minimumVisibleX; 
}

// Minimum visible Y coordinate of the map in the screen
int AGL::Map::getMinimumVisibleY() 
{ 
	return minimumVisibleY; 
}

// Maximum visible X coordinate of the map in the screen
int AGL::Map::getMaximumVisibleX() 
{ 
	return maximumVisibleX; 
}

// Maximum visible Y coordinate of the map in the screen
int AGL::Map::getMaximumVisibleY() 
{ 
	return maximumVisibleY; 
}

// Center of the map (in pixels)
AGL::IntVector2 AGL::Map::getCenter() 
{ 
	IntVector2 v(getAbsoluteSize().x / 2, getAbsoluteSize().y / 2);
	return v; 
}

AGL::Map::Map(int tileWidth, int tileHeight, int tileXCount, int tileYCount, AGL::IntVector2 &screenSize) 
{
   tileSize = new IntVector2(tileWidth, tileHeight);
   size = new IntVector2(tileXCount, tileYCount);
   camera = new Camera(screenSize);
}

AGL::Map::Map(int tileWidth, int tileHeight, int tileXCount, int tileYCount, AGL::Camera* _camera)
{
   tileSize = new IntVector2(tileWidth, tileHeight);
   size = new IntVector2(tileXCount, tileYCount);
   camera = _camera;
}

bool AGL::Map::isInMap(AGL::IntVector2 &point) 
{
   if (point.x >= 0 && point.y >= 0 && point.x < size->x && point.y < size->y)
       return true;

   return false;
}

