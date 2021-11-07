#include "header.h"
#include "CW4TileManager.h"
#include "BaseEngine.h"

CW4TileManager::CW4TileManager() : TileManager(40, 40, 15, 15) {
	image = ImageManager::loadImage("wall.png", true);
	image2 = ImageManager::loadImage("destination.png", true);	
	image3 = ImageManager::loadImage("grass.png", true);
	image4 = ImageManager::loadImage("water.png", true);
	image5 = ImageManager::loadImage("home.png", true);
}

CW4TileManager::~CW4TileManager() {
}

void CW4TileManager::virtDrawTileAt(
	BaseEngine* pEngine, // We don't need this but leave it here
	DrawingSurface* pSurface,
	int iMapX, int iMapY,
	int iStartPositionScreenX, int iStartPositionScreenY) const
{
	int iMapValue = getMapValue(iMapX, iMapY); 
	switch (iMapValue)
	{
		case 1:
			image.renderImageWithMask(pSurface,
				0, 0, iStartPositionScreenX, iStartPositionScreenY, image.getWidth(), image.getHeight());
			break;
		
		case 2:	
			image4.renderImageWithMask(pSurface,
				0, 0, iStartPositionScreenX, iStartPositionScreenY, image4.getWidth(), image4.getHeight());
			break;

		case 3:
			image4.renderImageWithMask(pSurface,
				0, 0, iStartPositionScreenX, iStartPositionScreenY, image4.getWidth(), image4.getHeight());
			image2.renderImageWithMask(pSurface,
				0, 0, iStartPositionScreenX+10, iStartPositionScreenY+10, image2.getWidth(), image2.getHeight());
			break;

		case 0:			
			image3.renderImageWithMask(pSurface,
				0, 0, iStartPositionScreenX, iStartPositionScreenY, image3.getWidth(), image3.getHeight());
			break;		
		case 5:
			image3.renderImageWithMask(pSurface,
				0, 0, iStartPositionScreenX, iStartPositionScreenY, image3.getWidth(), image3.getHeight());
			image5.renderImageWithMask(pSurface,
				0, 0, iStartPositionScreenX, iStartPositionScreenY, image5.getWidth(), image5.getHeight());
			break;
		case 99:
			//special case
			image4.renderImageWithMask(pSurface,
				0, 0, iStartPositionScreenX, iStartPositionScreenY, image4.getWidth(), image4.getHeight());
			break;
	}	
}
