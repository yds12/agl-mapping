#include "agl/mapping/camera.h"

#define CAM_MAX_VALUE 100000
#define CAM_MIN_VALUE -100000

AGL::Camera::Camera(AGL::IntVector2 &_screenSize, int originX, int originY, int cameraSpeed, int cameraMoveBound)
{
   moveBound = cameraMoveBound;
   
   moved = false;
   speed = cameraSpeed;
   origin = new IntVector2(originX, originY);
   screenSize = new IntVector2(_screenSize);
   minimumAllowedX = CAM_MIN_VALUE;
   minimumAllowedY = CAM_MIN_VALUE;
   maximumAllowedX = CAM_MAX_VALUE;
   maximumAllowedY = CAM_MAX_VALUE;
}

AGL::Camera::Camera(AGL::IntVector2 &_screenSize, int originX, int originY, int cameraSpeed)
{
   speed = cameraSpeed;
   
   moved = false;
   origin = new IntVector2(originX, originY);
   screenSize = new IntVector2(_screenSize);
   moveBound = 1;
   minimumAllowedX = CAM_MIN_VALUE;
   minimumAllowedY = CAM_MIN_VALUE;
   maximumAllowedX = CAM_MAX_VALUE;
   maximumAllowedY = CAM_MAX_VALUE;
}

AGL::Camera::Camera(AGL::IntVector2 &_screenSize, int originX, int originY)
{
   origin = new IntVector2(originX, originY);
   
   moved = false;
   screenSize = new IntVector2(_screenSize);
   speed = 1;
   moveBound = 1;
   minimumAllowedX = CAM_MIN_VALUE;
   minimumAllowedY = CAM_MIN_VALUE;
   maximumAllowedX = CAM_MAX_VALUE;
   maximumAllowedY = CAM_MAX_VALUE;
}

AGL::Camera::Camera(AGL::IntVector2 &_screenSize)
{
   screenSize = new IntVector2(_screenSize);
   origin = new IntVector2(0, 0);

   moved = false;
   speed = 1;
   moveBound = 1;
   
   minimumAllowedX = CAM_MIN_VALUE;
   minimumAllowedY = CAM_MIN_VALUE;
   maximumAllowedX = CAM_MAX_VALUE;
   maximumAllowedY = CAM_MAX_VALUE;
}

void AGL::Camera::update(bool moveUp, bool moveRight, bool moveDown, bool moveLeft, AGL::IntVector2 &mousePosition)
{
   update(mousePosition);
   update(moveUp, moveRight, moveDown, moveLeft);
}

void AGL::Camera::update(bool moveUp, bool moveRight, bool moveDown, bool moveLeft)
{
   if (moveUp && origin->y > minimumAllowedY)
   {
       moved = true;
       origin->y -= speed;
   }
   if (moveRight && origin->x < maximumAllowedX)
   {
       moved = true;
       origin->x += speed;
   }
   if (moveDown && origin->y < maximumAllowedY)
   {
       moved = true;
       origin->y += speed;
   }
   if (moveLeft && origin->x > minimumAllowedX)
   {
       moved = true;
       origin->x -= speed;
   }
}

void AGL::Camera::update(AGL::IntVector2 &mousePosition)
{
	if (mousePosition.x >= 0 && mousePosition.x < screenSize->x && mousePosition.y >= 0 && mousePosition.y < screenSize->y)
	{
		if (mousePosition.x < moveBound && origin->x > minimumAllowedX)
		{
			moved = true;
			origin->x -= speed;
		}
		else if (mousePosition.x >= (screenSize->x - moveBound) && origin->x < maximumAllowedX)
		{
			moved = true;
			origin->x += speed;
		}

		if (mousePosition.y < moveBound && origin->y > minimumAllowedY)
		{
			moved = true;
			origin->y -= speed;
		}
		else if (mousePosition.y >= (screenSize->y - moveBound) && origin->y < maximumAllowedY)
		{
			moved = true;
			origin->y += speed;
		}
	}
}

void AGL::Camera::setOrigin(AGL::IntVector2 &position) 
{
	if(*origin != position) moved = true;
	
   int x, y;

   if (position.x < minimumAllowedX)
       x = minimumAllowedX;
   else if (position.x > maximumAllowedX)
       x = maximumAllowedX;
   else
       x = position.x;

   if (position.y < minimumAllowedY)
       y = minimumAllowedY;
   else if (position.y > maximumAllowedY)
       y = maximumAllowedY;
   else
       y = position.y;

	delete(origin);
   origin = new IntVector2(x, y);
}

void AGL::Camera::setCenter(AGL::IntVector2 &position)
{
	IntVector2 center = getCenter();
	if(center != position) moved = true;

   int x, y;

   if (position.x - screenSize->x / 2 < minimumAllowedX)
       x = minimumAllowedX;
   else if (position.x - screenSize->x / 2 > maximumAllowedX)
       x = maximumAllowedX;
   else
       x = position.x - screenSize->x / 2;

   if (position.y - screenSize->y / 2 < minimumAllowedY)
       y = minimumAllowedY;
   else if (position.y - screenSize->y / 2 > maximumAllowedY)
       y = maximumAllowedY;
   else
       y = position.y - screenSize->y / 2;

	delete(origin);
   origin = new IntVector2(x, y);
}

AGL::IntVector2 AGL::Camera::getCenter()
{
	IntVector2 center(origin->x + screenSize->x / 2, origin->y + screenSize->y / 2);
	return center;
}

bool AGL::Camera::hasMoved()
{
	if(moved) 
	{
		moved = false;
		return true;
	}
	
	return false;
}
        
