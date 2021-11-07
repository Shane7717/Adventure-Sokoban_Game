#include "header.h"
#include "ImageManager.h"
#include "Scyxw3Engine.h"
#include "FroggerObject.h"
#include "MonsterObject.h"
#include "CollisionObject.h"



Scyxw3Engine::Scyxw3Engine()
{
}


Scyxw3Engine::~Scyxw3Engine()
{
}

Scyxw3TileManager Scyxw3Engine::tm;

void Scyxw3Engine::virtSetupBackgroundBuffer() {

	//Use image to set background (Requirement 1)
	SimpleImage backgroundImage = ImageManager::loadImage("space.jpg", true);
	backgroundImage = backgroundImage.resizeTo(this->getWindowWidth(), this->getWindowHeight());
	backgroundImage.renderImage(getBackgroundSurface(), 0, 0, 0, 0,
		this->getWindowWidth(), this->getWindowHeight());

	//Draw an image 
	SimpleImage image = ImageManager::loadImage("spaceShip.png", true);
	image = image.resizeTo(50, 50);
	image.renderImageWithMask(getBackgroundSurface(), 0, 0, 10, 10, image.getWidth(), image.getHeight());
	image.renderImageWithMask(getBackgroundSurface(), 0, 0, 60, 10, image.getWidth(), image.getHeight());
	image.renderImageWithMask(getBackgroundSurface(), 0, 0, 110, 10, image.getWidth(), image.getHeight());

	//Draw shapes
	drawBackgroundRectangle(10, 70, 60, 120, 0x00ff00);
	drawBackgroundOval(70, 70, 120, 120, 0xff0000);
	drawBackgroundTriangle(0, 700, 0, 800, 100, 800, 0x008080);
	drawBackgroundTriangle(1200, 800, 1300, 800, 1300, 700, 0x008080);

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			tm.setMapValue(i, j, rand());
		}
	}
	tm.setTopLeftPositionOnScreen(478, 224);
	tm.drawAllTiles(this, getBackgroundSurface());
}

void Scyxw3Engine::virtMouseDown(int iButton, int iX, int iY) {
	printf("Mouse clicked at %d %d\n", iX, iY);
}

int Scyxw3Engine::virtInitialiseObjects() {
	//Record the fact that we are about to change the array
	//So it doesn't get used elsewhere without reloading it
	drawableObjectsChanged();

	//Destroy any existing objects
	destroyOldObjects(true);

	//Create an array big enough for the number of objects that you want
	createObjectArray(3);

	//You must set the array entry after the last one that you create to NULL,
	//so that the system knows when to stop
	storeObjectInArray(0, new FroggerObject(this));
	storeObjectInArray(1, new MonsterObject(this));
	storeObjectInArray(2, new CollisionObject(this));

	//Note: We also need to destroy the objects, but the method at the 
	//top of this function will destroy all objects pointed at by the
	//array elements so we can ignore that here

	setAllObjectsVisible(true);
	return 0;
}

void Scyxw3Engine::virtDrawStringsUnderneath() {
	drawForegroundString(510, 10, "Out Of This World", 0xff0000, NULL);
}

void Scyxw3Engine::virtDrawStringsOnTop() {
	int xpos = getDisplayableObject(0)->getXCentre() + 17;
	int ypos = getDisplayableObject(0)->getYCentre() + 17;

	char a[11];
	const char *xstring = itoa(xpos, a, 10);
	char b[11];
	const char *ystring = itoa(ypos, b, 10);
	drawForegroundString(510, 40, "current position is: ", 0x00ff00, NULL);
	drawForegroundString(580, 70, xstring, 0xff0000, NULL);
	drawForegroundString(655, 70, ystring, 0xff0000, NULL);
}