#pragma once
#include "BoxObject.h"

class NormalBox : public BoxObject
{

public:
	NormalBox(BaseEngine* pEngine, int x, int y);
	~NormalBox();
	void virtDraw() override;
	void virtDoUpdate(int iCurrentTime) override;

};

