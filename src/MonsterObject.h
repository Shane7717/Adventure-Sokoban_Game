#pragma once
#include "DisplayableObject.h"

class MonsterObject : public DisplayableObject
{
public:
	MonsterObject(BaseEngine* pEngine);
	~MonsterObject();
	void virtDraw() override;
	void virtDoUpdate(int iCurrentTime) override;

};

