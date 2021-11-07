#pragma once
#include "BaseEngine.h"
#include "Scyxw3TileManager.h"

class Scyxw3Engine : public BaseEngine
{
public:
	Scyxw3Engine();
	~Scyxw3Engine();
	void virtSetupBackgroundBuffer() override;
	void virtMouseDown(int iButton, int iX, int iY) override;
	int virtInitialiseObjects() override;
	void virtDrawStringsUnderneath() override;
	void virtDrawStringsOnTop() override;

public:
	static Scyxw3TileManager tm;
};

