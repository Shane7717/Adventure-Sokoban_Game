#pragma once
#include "Monster.h"
class Insect : public Monster
{
public:
	Insect(BaseEngine* pEngine, int x, int y, CW4TileManager* tileManager);
	~Insect();
	void virtDraw() override;
	void virtDoUpdate(int iCurrentTime) override;

protected:
	SimpleImage leftImage;
	SimpleImage rightImage;
	SimpleImage downImage;
	SimpleImage upImage;
	SimpleImage mainImage;
	CW4TileManager* tm;
	int speed = 1;
	int lastChoice;
	int requiredXpos = 0;
	int requiredYpos = 0;
	bool signal = true;
	bool createOnce = true;	
};
