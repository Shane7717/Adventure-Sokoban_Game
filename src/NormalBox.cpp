#include "header.h"
#include "NormalBox.h"
#include "Scyxw3CW4Engine.h"
#include "RunningState.h"
#include "CollisionDetection.h"

NormalBox::NormalBox(BaseEngine *pEngine, int x, int y)
	: BoxObject(pEngine, x, y) {
}

NormalBox::~NormalBox(){
}

void NormalBox::virtDraw() {
	SimpleImage image = ImageManager::loadImage("box.png", true);
	//image = image.resizeTo(iImageSize, iImageSize);
	//Don't use this since memory will increase constantly

	image.renderImageWithMask(getEngine()->getForegroundSurface(),
		0, 0, m_iCurrentScreenX, m_iCurrentScreenY, image.getWidth(), image.getHeight());
}

void NormalBox::virtDoUpdate(int iCurrentTime) {

	// Ensure that the objects get redrawn on the display
	this->redrawDisplay();
}