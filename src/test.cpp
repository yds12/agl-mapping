#include <stdlib.h>
#include "agl/game.h"
#include "agl/drawer.h"

// ------------ Includes here ---------------
#include <iostream>
#include "agl/sound.h"
#include "agl/music.h"
#include "agl/joystick.h"
#include "agl/vector2.h"
#include "agl/intvector2.h"
#include "agl/gameobject.h"
#include "agl/support.h"
#include "agl/color.h"
#include "agl/mapping/map.h"
#include "agl/mapping/isometricmap.h"
#include "agl/mapping/ortogonalmap.h"
// ------------------------------------------

// ------------ Defines here ----------------
// ------------------------------------------

//const string fontPath = "/usr/share/fonts/dejavu/DejaVuSans.ttf";
//const string contentPath = "/home/USER/tests/agl/";
const string fontPath = "/usr/share/fonts/truetype/freefont/FreeMono.ttf";
const string contentPath = "/home/USER/test/";

AGL::Game* game = NULL;
AGL::Drawer* drawer = NULL;

// ------------ Declare variables here ------
AGL::Image* imagem = NULL;
AGL::Image* imagem2 = NULL;
AGL::Image* imagem3 = NULL;
AGL::IntVector2* position;
AGL::Keyboard* kb = NULL;
AGL::Mouse* ms = NULL;
AGL::GameObject* go = NULL;

AGL::IsometricMap* map = NULL;
AGL::OrtogonalMap* map2 = NULL;
// ------------------------------------------


void initialize()
{
	// ------------ Initialize variables here ---
	game = new AGL::Game;
	drawer = new AGL::Drawer;

	game->showMouse(true);
	kb = new AGL::Keyboard(false, false, true, true, false, false);
	ms = new AGL::Mouse;

	position = new AGL::IntVector2(10, 10);
	
	//AGL::Vector2 v(0, 1);
	//cout << v.toString() << endl;
	//cout << -PIDIV4 << endl;
	//v = v.rotate(-PIDIV4);
	//cout << v.toString() << endl;
	//game->quit = true;
	// ------------------------------------------
}

void loadContent()
{
	// ------------ Load content here -----------
	//imagem = new AGL::Image(AGL::Format::stringToChar(&(contentPath + "tileRect25x17.png")));
	imagem = new AGL::Image(AGL::Format::stringToChar(&(contentPath + "grass.png")));
	imagem2 = new AGL::Image(AGL::Format::stringToChar(&(contentPath + "water.png")));
	imagem3 = new AGL::Image(AGL::Format::stringToChar(&(contentPath + "mud.png")));
	map = new AGL::IsometricMap(40, 20, 100, 100, new AGL::Camera(*(drawer->screenSize), -10, -10, 10, 10));
	map2 = new AGL::OrtogonalMap(25, 17, 20, 20, new AGL::Camera(*(drawer->screenSize), -10, -10, 10, 10));
	// ------------------------------------------
}

void update()
{
	game->update(kb, ms, true);

	//if(game->gameCounter == 60) cout << 60 << " - " << game->cycleTime << endl;

	// ------------ Update the game here --------
	if(kb->isKeyDown(kb->getIndex(AGL::KEY_UP))) { map->camera->update(true, false, false, false); map2->camera->update(true, false, false, false); }
	if(kb->isKeyDown(kb->getIndex(AGL::KEY_DOWN))) { map->camera->update(false, false, true, false); map2->camera->update(false, false, true, false); }
	if(kb->isKeyDown(kb->getIndex(AGL::KEY_LEFT))) { map->camera->update(false, false, false, true); map2->camera->update(false, false, false, true); }
	if(kb->isKeyDown(kb->getIndex(AGL::KEY_RIGHT))) { map->camera->update(false, true, false, false); map2->camera->update(false, true, false, false); }
	if(kb->isKeyHeld(kb->getIndex(AGL::KEY_UP))) position->y--;
	if(kb->isKeyHeld(kb->getIndex(AGL::KEY_DOWN))) position->y++;
	if(kb->isKeyHeld(kb->getIndex(AGL::KEY_LEFT))) position->x--;
	if(kb->isKeyHeld(kb->getIndex(AGL::KEY_RIGHT))) position->x++;
	if(kb->isKeyDown(kb->getIndex(AGL::KEY_ESC))) game->quit = true;
	AGL::IntVector2 ss(1024, 768);
	if(kb->isKeyPressed(kb->getIndex(AGL::KEY_SPACE))) drawer->setScreen(ss, !drawer->fullScreen);
	if(kb->isKeyPressed(kb->getIndex(AGL::KEY_ENTER)))
	{
		
	}
	
	map->camera->update(*(ms->position));
	map2->camera->update(*(ms->position));
	// ------------------------------------------
}

void drawTile(int x, int y, int x2, int y2)
{
	// x e y são as coordenadas do tile (no mapa, não na tela)
	//cout << x << "," << y << endl;
	AGL::IntVector2 p(x2, y2);
	if((x + y) % 2 == 0) drawer->draw(imagem, p);
	else drawer->draw(imagem3, p);
	
	if(x == map->getPosition(*(ms->position)).x && y == map->getPosition(*(ms->position)).y)
		drawer->draw(imagem2, p);
}

void draw()
{
	drawer->clearScreen(AGL_COLOR_WHITE);

	// ------------ Draw objects here -----------
	//drawer->draw(imagem, new AGL::IntVector2(0, 0));
	AGL::Timer t;
	t.start();
	map->forEachVisible(drawTile);
	//cout << t.stop() << endl;
	//cout << map->getMinimumVisibleX() << ", " << map->getMinimumVisibleY() << " - " 
	//	<< map->getMaximumVisibleX() << ", " << map->getMaximumVisibleY() << endl;
	// ------------------------------------------
	//game->quit = true;
	drawer->updateScreen();
}

void unloadContent()
{
	// ------------ Unload objects here ---------
	// ------------------------------------------

	game->end();
}

/// Main method, initializes the program
int main(int argc, char *argv[])
{
	initialize();
	loadContent();

	while(!game->quit)
	{
		if(game->gameCounter % 60 == 0) 
			cout << (int) game->getFps(2) << endl;
			
		update();
		
		if(game->gameCounter % 2 == 0) 
			draw();
			
		//update();
		//draw();
	}

	unloadContent();

	return 0;
}
