#pragma once
#include "BaseEngine.h"
#include "MyTileManager.h"
class MyDemoA : public BaseEngine
{
public:
	MyDemoA();
	~MyDemoA();
	void virtSetupBackgroundBuffer() override;
	void virtMouseDown(int iButton, int iX, int iY) override;
	void virtKeyDown(int iKeyCode) override;

protected:
	MyTileManager tm;

public:
	int virtInitialiseObjects();
};

