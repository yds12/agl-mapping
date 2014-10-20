#ifndef _AGL_MAP_H
#define _AGL_MAP_H

#include "SDL/SDL.h"

#include "agl/intvector2.h"
#include "agl/mapping/camera.h"


/// @mainpage AGL - Aleva Game Library
/// @section Libraries
/// AGL Libraries
/// - <a href="../../index.html">agl: main AGL Library.</a>
/// - <a href="../../agl-graphics/html/index.html">agl-graphics: AGL Graphics Library.</a>
/// - agl-mapping: AGL Mapping Library.
/// - <a href="../../agl-motion/html/index.html">agl-motion: AGL Motion Library.</a>

namespace AGL
{
	/// Abstract class that represents a map
	class Map
	{
		protected:
			IntVector2* tileSize;
			IntVector2* size;

			int minimumVisibleX;
			int minimumVisibleY;
			int maximumVisibleX;
			int maximumVisibleY;
			
		public:			
        	/// Size of the tile
        	IntVector2 getTileSize();

        	/// Size of the map in tiles
        	IntVector2 getSize();
			
			/// Minimum visible X coordinate of the map in the screen
			int getMinimumVisibleX();

			/// Minimum visible Y coordinate of the map in the screen
			int getMinimumVisibleY();

			/// Maximum visible X coordinate of the map in the screen
			int getMaximumVisibleX();

			/// Maximum visible Y coordinate of the map in the screen
			int getMaximumVisibleY();
			
			/// Size of the map in pixels
			virtual IntVector2 getAbsoluteSize() = 0;
			
			/// Center of the map (in pixels)
			IntVector2 getCenter();

			/// Camera of the map
			Camera* camera;
			
			/// Creates a new instance of the Map class
			///
			/// @param tileWidth Width of the tile
			/// @param tileHeight Height of the tile
			/// @param tileXCount Number of tiles along the X axis
			/// @param tileYCount Number of tiles along the Y axis
			/// @param screenSize Size of the screen
			Map(int tileWidth, int tileHeight, int tileXCount, int tileYCount, IntVector2 &screenSize);

			/// Creates a new instance of the Map class
			/// 
			/// @param tileWidth Width of the tile
			/// @param tileHeight Height of the tile
			/// @param tileXCount Number of tiles along the X axis
			/// @param tileYCount Number of tiles along the Y axis
			/// @param _camera Camera of the map
			Map(int tileWidth, int tileHeight, int tileXCount, int tileYCount, Camera* _camera);
			
			/// Obtains the position in the map that corresponds to a given position in screen
			///
			/// @param screenPosition Position in the screen
			/// @return The corresponding position in the map
			virtual IntVector2 getPosition(IntVector2 &screenPosition) = 0;

			/// Obtains the position in the screen that corresponds to the top-left corner of the tile in a given position of the map
			///
			/// @param mapPosition Position in the map
			/// @return The corresponding position in the screen
			virtual IntVector2 getScreenPosition(IntVector2 &mapPosition) = 0;

			/// For each map point calls a draw method
			///
			/// @param drawMethod The draw method to be called
			virtual void forEach(void (*drawMethod)(int, int, int, int)) = 0;

			/// For each visible map point calls a draw method
			///
			/// @param drawMethod The draw method to be called
			virtual void forEachVisible(void (*drawMethod)(int, int, int, int)) = 0;

			/// Sets the map maximum and minimum coordinates in the visible screen
			virtual void setMapVisibleBounds() = 0;

			/// Verifies whether the point is in the map limits, or not
			///
			/// @param point Point to verify
			/// @return Whether the point is in the map bounds
			bool isInMap(IntVector2 &point);
	};
}

#endif

