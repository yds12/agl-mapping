#ifndef _AGL_ISOMETRICMAP_H
#define _AGL_ISOMETRICMAP_H

#include "SDL/SDL.h"

#include "agl/vector2.h"
#include "agl/intvector2.h"
#include "agl/mapping/map.h"

#define SQRT2 1.4142135624f
#define PIDIV4 0.7853981634f

namespace AGL
{
	/// Represents an isometric map, where the tile height in pixels must be an EVEN number. Odd number of pixels may cause bugs
	class IsometricMap : public Map
	{
		private:
			float tileRatio; // tile width / tile height
			int xOffset; // offset to put the map left corner in Y axis
			double squareSize; // size of the square side with diagonal = tile width
			double inverseSquareSize; // 1 / squareSize
			float xIsometricOffset; // offset to use when calculating the isometric coordinates
			float yIsometricOffset; // offset to use when calculating the isometric coordinates
			
			/// Initializes variables of the isometric map
			void initializeIsometricMap();
			
		public:
			/// The x offset to put the map left corner in the Y screen axis
			int getXOffset();
			
			/// Creates a new instance of the IsometricMap class
			/// 
			/// @param tileWidth Width of the tile
			/// @param tileHeight Height of the tile
			/// @param tileXCount Number of tiles along the X axis
			/// @param tileYCount Number of tiles along the Y axis
			/// @param screenSize Size of the screen
			IsometricMap(int tileWidth, int tileHeight, int tileXCount, int tileYCount, IntVector2 &screenSize);

			/// Creates a new instance of the IsometricMap class
			/// 
			/// @param tileWidth Width of the tile
			/// @param tileHeight Height of the tile
			/// @param tileXCount Number of tiles along the X axis
			/// @param tileYCount Number of tiles along the Y axis
			/// @param camera Camera of the map
			IsometricMap(int tileWidth, int tileHeight, int tileXCount, int tileYCount, Camera* camera); 
			
			/// Size of the map in pixels
			IntVector2 getAbsoluteSize();
			
			/// Obtains the position in the map that corresponds to a given position in screen
			///
			/// @param screenPosition Position in the screen
			/// @return The corresponding position in the map
			IntVector2 getPosition(IntVector2 &screenPosition);

			/// Obtains the position in the screen that corresponds to the top-left corner of the tile in a given position of the map
			///
			/// @param mapPosition Position in the map
			/// @return The corresponding position in the screen
			IntVector2 getScreenPosition(IntVector2 &mapPosition);

			/// For each map point calls a draw method
			///
			/// @param drawMethod The draw method to be called
			void forEach(void (*drawMethod)(int, int, int, int));

			/// For each visible map point calls a draw method
			///
			/// @param drawMethod The draw method to be called
			void forEachVisible(void (*drawMethod)(int, int, int, int));

			/// Sets the map maximum and minimum coordinates in the visible screen
			void setMapVisibleBounds();
	};
}

#endif

