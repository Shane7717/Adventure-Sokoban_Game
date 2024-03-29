#include "header.h"
#include "MyTileManager.h"



MyTileManager::MyTileManager()
	: TileManager(20, 20, 15, 15)
{
}


MyTileManager::~MyTileManager()
{
}

void MyTileManager::virtDrawTileAt(
	BaseEngine* pEngine, // We don't need this but maybe a student will so it is here to use if needed
	DrawingSurface* pSurface,
	int iMapX, int iMapY,
	int iStartPositionScreenX, int iStartPositionScreenY) const
{
	int iMapValue = getMapValue(iMapX, iMapY); // which was set to result of rand()
	unsigned int iColour = (unsigned int)((iMapValue & 0xf00) << 12) //red  lowest 12 bits of the random number in the map tile value
			+ (unsigned int)((iMapValue & 0xf0) << 8) //green
			+ (unsigned int)((iMapValue & 0xf) << 4); //blue
	pSurface->drawOval(
		iStartPositionScreenX,	//Left  
		iStartPositionScreenY,	//Top
		iStartPositionScreenX + getTileWidth() - 1,	//Right
		iStartPositionScreenY + getTileHeight() - 1,	//Bottom
		iColour
	);
}