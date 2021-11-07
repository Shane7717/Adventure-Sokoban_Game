#pragma once
#include "DisplayableObject.h"
class CollisionObject :
	public DisplayableObject
{
public:
	CollisionObject(BaseEngine* pEngine);
	~CollisionObject();
	void virtDraw() override;
	void virtDoUpdate(int iCurrentTime) override;

private:
	double xSpeed;
	double ySpeed;
	double m_dX;
	double m_dY;
};

