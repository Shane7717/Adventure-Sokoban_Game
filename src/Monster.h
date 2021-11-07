#pragma once
#include "DisplayableObject.h"
#include "BaseEngine.h"
#include "CW4TileManager.h"

class Monster : public DisplayableObject
{
public:
	Monster(BaseEngine* pEngine, int x, int y, CW4TileManager* tileManager);
	~Monster();
	virtual void virtDraw();
	virtual void virtDoUpdate(int iCurrentTime);
	void checkTileEdges();
	void checkTileEdges2();
	int squareDistance(int x1, int y1, int x2, int y2);
	
protected:
	CW4TileManager* tm;
};
