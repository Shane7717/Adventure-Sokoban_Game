#pragma once
#include "BaseEngine.h"

class BoxObject : public DisplayableObject
{

public:
	BoxObject(BaseEngine* pEngine, int x, int y);
	~BoxObject();	
	void virtDraw();
	void virtDoUpdate(int iCurrentTime);
};
