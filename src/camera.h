#ifndef _AGL_CAMERA_H
#define _AGL_CAMERA_H

#include "agl/intvector2.h"

namespace AGL
{
	/// Represents the visible area (in the screen) of a map
	class Camera
	{
		private:						
			bool moved;	
		
		public:		
			/// Origin of the camera. The point of the map that is the top-left corner of the screen
			IntVector2* origin;

			/// Speed of the camera movement (in pixels/"update")
			int speed;

			/// Distance from the screen limits (in pixels) that activates the camera movement by mouse
			int moveBound;

			/// Size of the screen
			IntVector2* screenSize;

			/// Minimum X coordinate allowed for the origin of the camera
			int minimumAllowedX;

			/// Minimum Y coordinate allowed for the origin of the camera
			int minimumAllowedY;

			/// Maximum X coordinate allowed for the origin of the camera
			int maximumAllowedX;

			/// Maximum Y coordinate allowed for the origin of the camera
			int maximumAllowedY;	
			
			/// Creates a new instance of the Camera class
			///
			/// @param originX X coordinate of the origin
			/// @param originY Y coordinate of the origin
			/// @param cameraSpeed Speed of the camera movement (in pixels/"update")
			/// @param cameraMoveBound Distance from the screen limits (in pixels) that activates the camera movement by mouse
			/// @param _screenSize Size of the screen
			Camera(IntVector2 &_screenSize, int originX, int originY, int cameraSpeed, int cameraMoveBound);

			/// Creates a new instance of the Camera class
			/// 
			/// @param originX X coordinate of the origin
			/// @param originY Y coordinate of the origin
			/// @param cameraSpeed Speed of the camera movement (in pixels/"update")
			/// @param _screenSize Size of the screen
			Camera(IntVector2 &_screenSize, int originX, int originY, int cameraSpeed);

			/// Creates a new instance of the Camera class
			/// 
			/// @param originX X coordinate of the origin
			/// @param originY Y coordinate of the origin
			/// @param _screenSize Size of the screen
			Camera(IntVector2 &_screenSize, int originX, int originY);

			/// Creates a new instance of the Camera class
			/// 
			/// @param _screenSize Size of the screen
			Camera(IntVector2 &_screenSize);

			/// Updates the camera, when it is not controlled by the mouse
			/// 
			/// @param moveUp Whether the up movement must be performed
			/// @param moveRight Whether the right movement must be performed
			/// @param moveDown Whether the down movement must be performed
			/// @param moveLeft Whether the left movement must be performed
			/// @param mousePosition Position of the mouse
			void update(bool moveUp, bool moveRight, bool moveDown, bool moveLeft, IntVector2 &mousePosition);

			/// Updates the camera, when it is not controlled by the mouse
			/// 
			/// @param moveUp Whether the up movement must be performed
			/// @param moveRight Whether the right movement must be performed
			/// @param moveDown Whether the down movement must be performed
			/// @param moveLeft Whether the left movement must be performed
			void update(bool moveUp, bool moveRight, bool moveDown, bool moveLeft);

			/// Updates the camera, when it is controlled by the mouse
			/// 
			/// @param mousePosition Position of the mouse cursor
			void update(IntVector2 &mousePosition);

			/// Sets the camera origin, verifying the camera bounds
			/// 
			/// @param position Position to set the camera
			void setOrigin(IntVector2 &position);

			/// Sets the camera origin by defining the point that will be centralized in the screen
			/// 
			/// @param position Center of the camera
			void setCenter(IntVector2 &position);
			
			/// Gets the center of the camera
			///
			/// @return the center of the camera 
			IntVector2 getCenter();
			
			/// Indicates whether the camera has moved since the last verification
			///
			/// @return Indicates whether the camera has moved since the last verification
			bool hasMoved();
	};
}

#endif

