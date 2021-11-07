#include "header.h"
#include "Scyxw3TileManager.h"
#include "Scyxw3Engine.h"
#include "BaseEngine.h"



Scyxw3TileManager::Scyxw3TileManager() : TileManager(34, 34, 10, 10)
{
}


Scyxw3TileManager::~Scyxw3TileManager()
{
}

void Scyxw3TileManager::virtDrawTileAt(
	BaseEngine* pEngine, // We don't need this but leave it here
	DrawingSurface* pSurface,
	int iMapX, int iMapY,
	int iStartPositionScreenX, int iStartPositionScreenY) const
{
	int iMapValue = getMapValue(iMapX, iMapY); // which was set to result of rand()
	//unsigned int iColour = 0x008080 * ((iMapX + iMapY + iMapValue) % 16);
	unsigned int iColour = 0x008080 * ((iMapX + iMapY + iMapValue) % 500);
	if (iMapX == 4 && iMapY == 9) {
		pSurface->drawOval(
			iStartPositionScreenX,	//Left  
			iStartPositionScreenY,	//Top
			iStartPositionScreenX + getTileWidth() - 1,	//Right
			iStartPositionScreenY + getTileHeight() - 1,	//Bottom
			0x00ff00
		);
	}
	else if (iMapX == 6 && iMapY == 0) {
		pSurface->drawOval(
			iStartPositionScreenX,	//Left  
			iStartPositionScreenY,	//Top
			iStartPositionScreenX + getTileWidth() - 1,	//Right
			iStartPositionScreenY + getTileHeight() - 1,	//Bottom
			0xff0000
		);
	}
	else {
		pSurface->drawThickLine(
			iStartPositionScreenX,	//Left  
			iStartPositionScreenY,	//Top
			iStartPositionScreenX + getTileWidth() - 1,	//Right
			iStartPositionScreenY + getTileHeight() - 1,	//Bottom
			iColour,
			6
		);
	}
}
