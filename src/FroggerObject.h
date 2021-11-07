#pragma once
#include "DisplayableObject.h"


class FroggerObject : public DisplayableObject
{
public:
	FroggerObject(BaseEngine* pEngine);
	~FroggerObject();
	void virtDraw() override; 
	void virtDoUpdate(int iCurrentTime) override;

protected:
	int iLastXpos = 0;
	int iLastYpos = 0;
};
