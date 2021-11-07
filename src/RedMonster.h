#pragma once
#include "Monster.h"
#include "CW4TileManager.h"

class RedMonster : public Monster
{
public:
	RedMonster(BaseEngine* pEngine, int x, int y, CW4TileManager* tileManager);
	~RedMonster();
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
	bool minusOnce = true;
};
