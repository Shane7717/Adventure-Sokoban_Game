#pragma once
#include "BaseEngine.h"
#include "DisplayableObject.h"

class CW4TileManager;

class MainCharacter : public DisplayableObject
{
public:
	MainCharacter(BaseEngine* pEngine, int x, int y, CW4TileManager* tileManager);
	~MainCharacter();
	void virtDraw() override;
	void virtDoUpdate(int iCurrentTime) override;

protected:
	int wTimes = 0;
	int sTimes = 0;
	int aTimes = 0;
	int dTimes = 0;

public:
	SimpleImage imageUp;
	SimpleImage imageDown;
	SimpleImage imageLeft;
	SimpleImage imageRight;
	SimpleImage mainImage;
	CW4TileManager* tm;
	BaseEngine* engine;
	bool createOnce = true;
};
