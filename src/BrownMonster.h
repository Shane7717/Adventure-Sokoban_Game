#pragma once
#include "Monster.h"
#include "OperatorOverload.h"

class BrownMonster : public Monster
{
public:
	BrownMonster(BaseEngine* pEngine, int x, int y, CW4TileManager* tileManager);
	~BrownMonster();
	void virtDraw() override;
	void virtDoUpdate(int iCurrentTime) override;

protected:	
	SimpleImage leftImage;
	SimpleImage rightImage;
	SimpleImage mainImage;
	CW4TileManager* tm;
	int speed = 1;
	int lastChoice;
	int requiredXpos = 0;
	int requiredYpos = 0;
	bool signal = true;
	int goalXpos = 0;
	int goalYpos = 0;
	bool getToWall = false;
	int randomTimes = 5;
	OperatorOverload oo;
};
