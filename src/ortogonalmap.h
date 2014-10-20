#ifndef _AGL_ORTOGONALMAP_H
#define _AGL_ORTOGONALMAP_H

#include "SDL/SDL.h"

#include "agl/intvector2.h"
#include "agl/mapping/map.h"

namespace AGL
{
	/// Represents an ortogonal map
	class OrtogonalMap : public Map
	{
		private:
			
		public:			
			/// Creates a new instance of the OrtogonalMap class
			/// 
			/// @param tileWidth Width of the tile
			/// @param tileHeight Height of the tile
			/// @param tileXCount Number of tiles along the X axis
			/// @param tileYCount Number of tiles along the Y axis
			/// @param screenSize Size of the screen
			OrtogonalMap(int tileWidth, int tileHeight, int tileXCount, int tileYCount, IntVector2 &screenSize);

			/// Creates a new instance of the OrtogonalMap class
			/// 
			/// @param tileWidth Width of the tile
			/// @param tileHeight Height of the tile
			/// @param tileXCount Number of tiles along the X axis
			/// @param tileYCount Number of tiles along the Y axis
			/// @param camera Camera of the map
			OrtogonalMap(int tileWidth, int tileHeight, int tileXCount, int tileYCount, Camera* camera); 
			
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

