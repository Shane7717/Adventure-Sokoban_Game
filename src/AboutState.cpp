#include "header.h"
#include "AboutState.h"
#include "BaseEngine.h"
#include "Scyxw3CW4Engine.h"
#include "MenuState.h"
#include "MappableImageObject.h"

AboutState::AboutState(BaseEngine* p_engine) : rotator(0.0)
{
	engine = p_engine;
}

AboutState::~AboutState() {
}

void AboutState::setupBackgroundBuffer() {
	//Use image to set background 
	SimpleImage backgroundImage = ImageManager::loadImage("menuImage.png", true);
	backgroundImage.renderImage(engine->getBackgroundSurface(), 0, 0, 0, 0,
		engine->getWindowWidth(), engine->getWindowHeight());

	//Draw an image
	SimpleImage aboutImage = ImageManager::loadImage("about.png", true);	
	aboutImage = aboutImage.resizeTo(450, 450);
	aboutImage.renderImageWithMask(engine->getBackgroundSurface(), 0, 0, 820, 140, aboutImage.getWidth(), aboutImage.getHeight());
		
	//Draw buttons
	SimpleImage button = ImageManager::loadImage("keys.png", true);
	button = button.resizeTo(120, 100);
	button.renderImageWithMask(engine->getBackgroundSurface(), 0, 0, 130, 95, button.getWidth(), button.getHeight());

	SimpleImage image = ImageManager::loadImage("moveBoxes.png", true);
	image = image.resizeTo(120, 90);
	image.renderImageWithMask(engine->getBackgroundSurface(), 0, 0, 130, 220, image.getWidth(), image.getHeight());

	SimpleImage image2 = ImageManager::loadImage("gohome.png", true);
	image2 = image2.resizeTo(100, 50);
	image2.renderImageWithMask(engine->getBackgroundSurface(), 0, 0, 140, 340, image2.getWidth(), image2.getHeight());

	SimpleImage image3 = ImageManager::loadImage("RedMonsterRight.png", true);	
	image3 = image3.resizeTo(360, 60);
	image3.renderImageWithMask(engine->getBackgroundSurface(), image3.getWidth() / 6, 0, 160, 415, image3.getWidth() / 6, image3.getHeight());

	SimpleImage image4 = ImageManager::loadImage("GreenMonsterRight.png", true);
	image4 = image4.resizeTo(300, 60);
	image4.renderImageWithMask(engine->getBackgroundSurface(), image4.getWidth() / 5, 0, 160, 495, image4.getWidth() / 5, image4.getHeight());

	SimpleImage image5 = ImageManager::loadImage("BrownMonsterRight.png", true);
	image5 = image5.resizeTo(300, 60);
	image5.renderImageWithMask(engine->getBackgroundSurface(), image5.getWidth() / 5, 0, 160, 575, image5.getWidth() / 5, image5.getHeight());

	SimpleImage image6 = ImageManager::loadImage("insectRight.png", true);
	image6 = image6.resizeTo(360, 60);
	image6.renderImageWithMask(engine->getBackgroundSurface(), image6.getWidth() / 6, 0, 160, 655, image6.getWidth() / 6, image6.getHeight());

}

void AboutState::drawStringsUnderneath() {
	if (aboutPageSelection == 0)
		engine->drawForegroundString(600, 690, "Back", 0xcc3333, engine->getFont("Cornerstone Regular.ttf", 40));
	else
		engine->drawForegroundString(600, 690, "Back", 0xffcc99, engine->getFont("Cornerstone Regular.ttf", 40));

	engine->drawForegroundString(250, 100,  "Control: W A S D", 0xffff99, engine->getFont("Cornerstone Regular.ttf", 24));
	engine->drawForegroundString(255, 215, "Step 1: Push Boxes To Destinations (Tiles With Cubes Over)", 0xffff99, engine->getFont("Cornerstone Regular.ttf", 24));
	engine->drawForegroundString(255, 325, "Step 2: Move Player To Go Home (To Continue The Next Level)", 0xffff99, engine->getFont("Cornerstone Regular.ttf", 24));
	engine->drawForegroundString(255, 405, "Meet Red Giants Will Lose Marks - They Have Constant Speed", 0xff0000, engine->getFont("Cornerstone Regular.ttf", 24));
	engine->drawForegroundString(255, 485, "Meet Green Monsters Will Lose Marks - They Have Changing Speed", 0x00ff00, engine->getFont("Cornerstone Regular.ttf", 24));
	engine->drawForegroundString(255, 565, "Meet Brown Monsters Will Reset Position - They Will Chase You !!!", 0xffcc00, engine->getFont("Cornerstone Regular.ttf", 24));
	engine->drawForegroundString(255, 645, "Meet Blue Monsters Will Win Marks - They Are Bonus !!!", 0x66ffff, engine->getFont("Cornerstone Regular.ttf", 24));
}

void AboutState::mouseDown(int iButton, int iX, int iY) {
	if (iX >= 570 && iX <= 730 && iY >= 690 && iY <= 734) {
		Scyxw3CW4Engine::bs = Scyxw3CW4Engine::menuState;
		engine->lockAndSetupBackground();
		engine->virtInitialiseObjects();
		engine->redrawDisplay();
	}
}

void AboutState::mouseMoved(int iX, int iY) {	
	if (iX >= 570 && iX <= 730 && iY >= 690 && iY <= 734) {
		aboutPageSelection = 0;
		engine->redrawDisplay();		
	}
	else {
		aboutPageSelection = -1;
		engine->redrawDisplay();
	}	
}

int AboutState::initialiseObjects() {
	engine->drawableObjectsChanged();
	// Destroy any existing objects
	engine->destroyOldObjects(true);
	
	MappableImageObject* ob = new MappableImageObject(&rotator, 55, 55, engine, "menuImage2.png", false);
	ob->setTransparencyColour(ob->getPixelColour(0, 0));
	engine->appendObjectToArray(ob);

	return 0;
}

void AboutState::virtMainLoopDoBeforeUpdate() {
	//++m_iOffset;	
	if (engine->getModifiedTime() % 500 >= 0 && engine->getModifiedTime() % 500 < 250) {
		m_iOffset = (m_iOffset + 1) % (engine->getWindowHeight());
	} 
	else if (engine->getModifiedTime() % 500 >= 250
		&& engine->getModifiedTime() % 500 < 500 && m_iOffset > 0){
		m_iOffset = (m_iOffset - 1) % (engine->getWindowHeight());
	}
	
	int offset = engine->getModifiedTime() / 10;
	if (engine->getModifiedTime() % 1000 >= 0 && engine->getModifiedTime() % 1000 < 500)
		rotator.setRotation((double)offset / -40.0);
	else if (engine->getModifiedTime() % 1000 >= 500 && engine->getModifiedTime() % 1000 < 1000)
		rotator.setRotation((double)offset / 40.0);

	engine->redrawDisplay();
}

void AboutState::copyAllBackgroundBuffer() {
	(engine->getForegroundSurface())->copyRectangleFrom(engine->getBackgroundSurface(), 0, 0, engine->getWindowWidth(), engine->getWindowHeight(), 0, m_iOffset);
	(engine->getForegroundSurface())->copyRectangleFrom(engine->getBackgroundSurface(), 0, engine->getWindowHeight() - m_iOffset, engine->getWindowWidth(), engine->getWindowHeight(), 0, m_iOffset - engine->getWindowHeight());
	//	m_pForegroundSurface->copyRectangleFrom(m_pBackgroundSurface, 0, 0, getWindowWidth(), getWindowHeight(), 0, m_iOffset);
	//	m_pForegroundSurface->copyRectangleFrom(m_pBackgroundSurface, 0, getWindowHeight() - m_iOffset, getWindowWidth(), getWindowHeight(), 0, m_iOffset - getWindowHeight());
}

bool AboutState::mapCoordinates(double& x, double& y, const SimpleImage& image) {
	
	int offset = engine->getModifiedTime() / 10;			
	if (x < 0) return false;
	if (y < 0) return false;
	if (x >= (image.getWidth() - 0.5)) return false;
	if (y >= (image.getHeight() - 0.5)) return false;

	// Shift offset to the centre of the image, so we can rotate around centre
	x -= image.getWidth() / 2;
	y -= image.getHeight() / 2;

	// Rotate	
	double angle = atan(y / (x + 0.0001));
	if (x < 0)
		angle += M_PI;
	double temp = ::sqrt(x*x + y * y);
	angle += (double)offset / 100;

	x = temp * ::cos(angle) + image.getWidth() / 2;
	y = temp * ::sin(angle) + image.getHeight() / 2;

	if (x < 0) return false;
	if (y < 0) return false;
	if (x >= (image.getWidth() - 0.5)) return false;
	if (y >= (image.getHeight() - 0.5)) return false;

	return true;
}