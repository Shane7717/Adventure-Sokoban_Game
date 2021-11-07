#pragma once
#include "TileManager.h"
#include "ImageManager.h"

class CW4TileManager : public TileManager
{
public:
	CW4TileManager();
	~CW4TileManager();
	void virtDrawTileAt(
		BaseEngine* pEngine,
		DrawingSurface* pSurface,
		int iMapX, int iMapY,
		int iStartPositionScreenX, int iStartPositionScreenY) const override;

protected:
	SimpleImage image;
	SimpleImage image2;
	SimpleImage image3;
	SimpleImage image4;
	SimpleImage image5;
};
