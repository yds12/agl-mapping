#include "agl/mapping/isometricmap.h"

AGL::IsometricMap::IsometricMap(int tileWidth, int tileHeight, int tileXCount, int tileYCount, AGL::IntVector2 &screenSize) :
   Map(tileWidth, tileHeight, tileXCount, tileYCount, screenSize)
{
   initializeIsometricMap();
}

AGL::IsometricMap::IsometricMap(int tileWidth, int tileHeight, int tileXCount, int tileYCount, AGL::Camera* camera) : 
   Map(tileWidth, tileHeight, tileXCount, tileYCount, camera)
{
   initializeIsometricMap();
}

void AGL::IsometricMap::initializeIsometricMap()
{
   xOffset = (int)((((float)size->y / 2.0f) - 0.5) * (float)tileSize->x);
   tileRatio = (float)tileSize->x / (float)tileSize->y;
   squareSize = (float)tileSize->x * 0.5 * SQRT2;
   inverseSquareSize = 1 / squareSize;
   xIsometricOffset = (float)(((float)(size->x + size->y) / 2.0f * (float)tileSize->x - squareSize * (float)size->x) / 2);
   yIsometricOffset = (float)(((float)(size->x + size->y) / 2.0f * (float)tileSize->x - squareSize * (float)size->y) / 2);
}

AGL::IntVector2 AGL::IsometricMap::getAbsoluteSize()
{
	float avg = (float)(size->x + size->y) / 2.0f;
	IntVector2 v((int)(avg * tileSize->x), (int)(avg * tileSize->y));
	return v;
}

int AGL::IsometricMap::getXOffset() 
{ 
	return xOffset;
}

AGL::IntVector2 AGL::IsometricMap::getPosition(AGL::IntVector2 &screenPosition)
{
	IntVector2 center = getCenter();
   Vector2 mapCenter2(center);

   // Escreve a posição em relação a origem (no centro do mapa)
   IntVector2 v1 = screenPosition + (*(camera->origin));
   IntVector2 v2 = v1 - center;
   Vector2 position(v2);

   // Como a altura do losango é a metade da largura, multiplica por 2
   position.y *= tileRatio;

   // O centro do mapa também é deslocado
   mapCenter2.y *= tileRatio;

   // Rotaciona o vetor posição -45°
   Vector2 p2 = position.rotate(-PIDIV4);
   position = p2;

   // Retorna a referência da posição para o canto da tela
   position += mapCenter2;

   // O mapa quadrado está centralizado no centro do losango, precisa retornar ao canto da tela
   position.x -= xIsometricOffset;
   position.y -= yIsometricOffset;

   // Depois divide pelo tamanho do quadrado para achar a posição da matriz
   position.x = ((int)(position.x * inverseSquareSize));
   position.y = ((int)(position.y * inverseSquareSize));

	IntVector2 p = position.toIntVector2();
   return p;
}

AGL::IntVector2 AGL::IsometricMap::getScreenPosition(AGL::IntVector2 &mapPosition)
{
	IntVector2 v((-mapPosition.y * (tileSize->x / 2)) + (mapPosition.x * (tileSize->x / 2)) - camera->origin->x,
       (mapPosition.y * (tileSize->y / 2)) + (mapPosition.x * (tileSize->y / 2)) - camera->origin->y);
   return v;
}

void AGL::IsometricMap::forEach(void (*drawMethod)(int, int, int, int))
{
   int width = tileSize->x / 2;
   int height = tileSize->y / 2;
   
   for (int j = 0; j < size->y; j++)
   {
       int wid = -j * width;
       int hei = j * height;

       for (int i = 0; i < size->x; i++)
       {
           int wid2 = wid + (i * width);
           int hei2 = hei + (i * height);

           (*drawMethod)(i, j, wid2 - camera->origin->x + xOffset, hei2 - camera->origin->y);
       }
   }
}

void AGL::IsometricMap::forEachVisible(void (*drawMethod)(int, int, int, int)) 
{
	if(camera->hasMoved()) setMapVisibleBounds();
	
   int width = tileSize->x / 2;
   int height = tileSize->y / 2;

   for (int j = minimumVisibleY; j <= maximumVisibleY; j++)
   {
       int wid = -j * width;
       int hei = j * height;

       for (int i = minimumVisibleX; i <= maximumVisibleX; i++)
       {
           int wid2 = wid + (i * width);
           int hei2 = hei + (i * height);

           (*drawMethod)(i, j, wid2 - camera->origin->x + xOffset, hei2 - camera->origin->y);
       }
   }
}

void AGL::IsometricMap::setMapVisibleBounds()
{
	IntVector2 v1(0, 0);
   IntVector2 ul = getPosition(v1);
   IntVector2 v2(camera->screenSize->x - 1, 0);
   IntVector2 ur = getPosition(v2);
   IntVector2 v3(0, camera->screenSize->y - 1);
   IntVector2 dl = getPosition(v3);
   IntVector2 v4(camera->screenSize->x - 1, camera->screenSize->y - 1);
   IntVector2 dr = getPosition(v4);

   minimumVisibleY = ur.y;
   minimumVisibleX = ul.x;
   maximumVisibleY = dl.y;
   maximumVisibleX = dr.x;

   if (minimumVisibleY < 0) minimumVisibleY = 0;
   else if (minimumVisibleY > size->y - 1) minimumVisibleY = size->y - 1;

   if (maximumVisibleY < 0) maximumVisibleY = 0;
   else if (maximumVisibleY > size->y - 1) maximumVisibleY = size->y - 1;

   if (minimumVisibleX < 0) minimumVisibleX = 0;
   else if (minimumVisibleX > size->x - 1) minimumVisibleX = size->x - 1;

   if (maximumVisibleX < 0) maximumVisibleX = 0;
   else if (maximumVisibleX > size->x - 1) maximumVisibleX = size->x - 1;
}

