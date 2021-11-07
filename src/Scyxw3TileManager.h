#pragma once
#include "TileManager.h"
class Scyxw3TileManager :
	public TileManager
{
public:
	Scyxw3TileManager();
	~Scyxw3TileManager();
	void virtDrawTileAt(
		BaseEngine* pEngine,
		DrawingSurface* pSurface,
		int iMapX, int iMapY,
		int iStartPositionScreenX, int iStartPositionScreenY) const override;
};

