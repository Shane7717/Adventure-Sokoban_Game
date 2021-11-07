#include "header.h"
#include "RunningState.h"
#include "BaseEngine.h"
#include "CW4TileManager.h"
#include "MainCharacter.h"
#include "NormalBox.h"
#include "Scyxw3CW4Engine.h"
#include <fstream>
#include "SDL_mixer.h"
#include "EnterNameState.h"
#include "RedMonster.h"
#include "GreenMonster.h"
#include "BrownMonster.h"

RunningState::RunningState(BaseEngine* p_engine) 	
{
	engine = p_engine;
	//playMusic();
	//startPlayTime = 1;
}

RunningState::~RunningState() {
	delete tm;	
}

int RunningState::currentLevel = 1;
int RunningState::currentNumBoxes;
int RunningState::loadOnce = 1;
int RunningState::currentTime = 0;
int RunningState::startPlayTime = 1;
int RunningState::currentScore = 100;
int RunningState::mainX;
int RunningState::mainY;

void RunningState::setupBackgroundBuffer() {	
	//Use image to set background 
	if (loadOnce == 1) {
		SimpleImage backgroundImage = ImageManager::loadImage("runningBackground.png", true);
		backgroundImage.renderImage(engine->getBackgroundSurface(), 0, 0, 0, 0,
			engine->getWindowWidth(), engine->getWindowHeight());
	}

	//Draw Tiles
	//default 0 represents emtpy tile (transparent tiles)
	//1 represents the walls
	//2 represents the floors
	//3 represents destination tile
	
	string strFileName = "level" + to_string(currentLevel) + "Map.txt";	
	ifstream file;		
	file.open(strFileName);
	if (!file) {
		cout << "Failed to open the file" << endl;
		exit(1);
	}

	int xPos;
	int yPos;
	int tileType;
	file >> currentLevel;

	while (file) {
		file >> xPos;
		file >> yPos;
		file >> tileType;
		tm->setMapValue(xPos, yPos, tileType);
	}
	file.close();

	tm->setMapValue(14, 0, 5);
	tm->setMapValue(13, 0, 1);
	tm->setMapValue(13, 1, 1);
	tm->setMapValue(14, 1, 1);

	tm->setMapValue(0, 7, 1);
	tm->setMapValue(1, 5, 1);
//	tm->setMapValue(1, 7, 1);
	tm->setMapValue(1, 9, 1);
//	tm->setMapValue(2, 5, 1);
//	tm->setMapValue(2, 9, 1);
//	tm->setMapValue(12, 4, 1);
//	tm->setMapValue(12, 8, 1);
	tm->setMapValue(13, 4, 1);
//	tm->setMapValue(13, 6, 1);
	tm->setMapValue(13, 8, 1);
	tm->setMapValue(14, 6, 1);
	tm->setMapValue(2, 12, 1);
	tm->setMapValue(3, 12, 1);
	tm->setMapValue(6, 12, 1);	
	tm->setMapValue(8, 12, 1);
	tm->setMapValue(11, 12, 1);
	tm->setMapValue(12, 12, 1);

	tm->setMapValue(xPos, yPos, tileType);
	tm->setTopLeftPositionOnScreen(360, 155);
	tm->drawAllTiles(engine, engine->getBackgroundSurface());
	
	//Draw buttons
	if (loadOnce == 1) {
		SimpleImage button = ImageManager::loadImage("buttonImage2.png", true);
	//	button = button.resizeTo(100, 60);
		button.renderImageWithMask(engine->getBackgroundSurface(), 0, 0, 1080, 185, button.getWidth(), button.getHeight());
		button.renderImageWithMask(engine->getBackgroundSurface(), 0, 0, 1080, 285, button.getWidth(), button.getHeight());
		button.renderImageWithMask(engine->getBackgroundSurface(), 0, 0, 1080, 385, button.getWidth(), button.getHeight());
		button.renderImageWithMask(engine->getBackgroundSurface(), 0, 0, 1080, 485, button.getWidth(), button.getHeight());
	}
	loadOnce++;	
}

void RunningState::drawStringsUnderneath() {
	//Draw an string on the screen
	engine->drawForegroundString(400, 50, "S o k o b a n*", 0xff9900, engine->getFont("stocky.ttf", 80));
	engine->drawForegroundString(610, 160, "Level", 0xff0000, NULL);

	//Convert to the correct data type, and draw 'level' on screen
	char a[11];
	const char *string = itoa(currentLevel, a, 10);
	engine->drawForegroundString(700, 160, a, 0xff0000, NULL);

	//Draw the player's name on screen
	engine->drawForegroundString(45, 290, "Hello, ", 0x00ffcc, engine->getFont("Cornerstone Regular.ttf", 22));
	engine->drawForegroundString(115, 282, (Scyxw3CW4Engine::enterNameState)->name.data(), 0x00ffcc, engine->getFont("Cornerstone Regular.ttf", 32));

	engine->drawForegroundString(30, 360, "Your Current Score: ", 0x66ffff, NULL);
	//Convert to the correct data type, and draw current score on screen
	char b[11];
	const char *string2 = itoa(currentScore, b, 10);
	engine->drawForegroundString(155, 390, b, 0x66ffff, NULL);


	engine->drawForegroundString(980, 240, "Save current game state", 0xffcc66, engine->getFont("Cornerstone Regular.ttf", 20));
	engine->drawForegroundString(992, 340, "Load saved game state", 0xffcc66, engine->getFont("Cornerstone Regular.ttf", 20));
	engine->drawForegroundString(978, 440, "Reset current game level", 0xffcc66, engine->getFont("Cornerstone Regular.ttf", 20));
	engine->drawForegroundString(1046, 540, "Quit This Game", 0xffcc66, engine->getFont("Cornerstone Regular.ttf", 20));

	if (gameSelection == 0) {
		engine->drawForegroundString(1100, 200, "Save", 0xffffff, engine->getFont("Cornerstone Regular.ttf", 23));
	}
	else {
		engine->drawForegroundString(1100, 200, "Save", 0x0000ff, engine->getFont("Cornerstone Regular.ttf", 23));
	}

	if (gameSelection == 1) {
		engine->drawForegroundString(1100, 300, "Load", 0xffffff, engine->getFont("Cornerstone Regular.ttf", 23));
	}
	else {
		engine->drawForegroundString(1100, 300, "Load", 0x0000ff, engine->getFont("Cornerstone Regular.ttf", 23));
	}

	if (gameSelection == 2) {
		engine->drawForegroundString(1095, 400, "Reset", 0xffffff, engine->getFont("Cornerstone Regular.ttf", 23));
	}
	else {
		engine->drawForegroundString(1095, 400, "Reset", 0x0000ff, engine->getFont("Cornerstone Regular.ttf", 23));
	}

	if (gameSelection == 3) {
		engine->drawForegroundString(1105, 500, "Quit", 0xffffff, engine->getFont("Cornerstone Regular.ttf", 23));
	}
	else {
		engine->drawForegroundString(1105, 500, "Quit", 0x0000ff, engine->getFont("Cornerstone Regular.ttf", 23));
	}

	engine->drawForegroundString(453, 700, "You Can Press 'SPACE' To Pause", 0x00ffff, engine->getFont("Cornerstone Regular.ttf", 21));
}

int RunningState::initialiseObjects() {
	//Record the fact that we are about to change the array
	//So it doesn't get used elsewhere without reloading it
	engine->drawableObjectsChanged();

	//Destroy any existing objects
	engine->destroyOldObjects(true);
	
	//Create an array big enough for the number of objects that you want
	engine->createObjectArray(20);

	//You must set the array entry after the last one that you create to NULL,
	//so that the system knows when to stop
	string strFileName = "level" + to_string(currentLevel) + "Objects.txt";
	ifstream file;
	file.open(strFileName);
	if (!file) {
		cout << "Failed to open the file" << endl;
		exit(1);
	}

	int xPos;
	int yPos;
	int type;
	int index = 1;
	file >> currentNumBoxes;
	file >> xPos;
	file >> yPos;
	file >> type;
	mainX = xPos;
	mainY = yPos;
	engine->storeObjectInArray(0, new MainCharacter(engine, 360 + 40 * xPos, 155 + 40 * yPos, tm));	
	engine->getDisplayableObject(0)->setShouldDeleteOnRemoval(true);
			 
	file >> xPos;
	file >> yPos;
	file >> type;
	while (file) {		
		if (type == 1) {
			engine->storeObjectInArray(index, new NormalBox(engine, 360 + 40 * xPos, 155 + 40 * yPos));
			engine->getDisplayableObject(index)->setShouldDeleteOnRemoval(true);
			file >> xPos;
			file >> yPos;
			file >> type;
			index++;
		}
		else if (type == 2) {
			engine->storeObjectInArray(index, new RedMonster(engine, 360 + 40 * xPos, 155 + 40 * yPos, tm));
			engine->getDisplayableObject(index)->setDefaultColour(2);
			engine->getDisplayableObject(index)->setShouldDeleteOnRemoval(true);
			file >> xPos;
			file >> yPos;
			file >> type;
			index++;
		}
		else if (type == 3) {
			engine->storeObjectInArray(index, new GreenMonster(engine, 360 + 40 * xPos, 155 + 40 * yPos, tm));
			engine->getDisplayableObject(index)->setDefaultColour(3);
			engine->getDisplayableObject(index)->setShouldDeleteOnRemoval(true);
			file >> xPos;
			file >> yPos;
			file >> type;
			index++;
		} 
		else if (type == 4) {
			engine->storeObjectInArray(index, new BrownMonster(engine, 360 + 40 * xPos, 155 + 40 * yPos, tm));
			engine->getDisplayableObject(index)->setDefaultColour(4);
			engine->getDisplayableObject(index)->setShouldDeleteOnRemoval(true);
			file >> xPos;
			file >> yPos;
			file >> type;
			index++;
		}
	}
	file.close();
	//engine->storeObjectInArray(index, NULL);
	
	
	//Note: We also need to destroy the objects, but the method at the 
	//top of this function will destroy all objects pointed at by the
	//array elements so we can ignore that here
	engine->setAllObjectsVisible(true);		
	return 0;
}

void RunningState::mouseMoved(int iX, int iY) {
	int selected = 0;

	//If player's mouse moves over the "save" button
	if (iX >= 1080 && iX <= 1180 && iY >= 185 && iY <= 235) {
		gameSelection = 0;
		selected = 1;
		engine->redrawDisplay();
	}
	if (iX >= 1080 && iX <= 1180 && iY >= 285 && iY <= 335) {
		gameSelection = 1;
		selected = 1;
		engine->redrawDisplay();
	}
	if (iX >= 1080 && iX <= 1180 && iY >= 385 && iY <= 435) {
		gameSelection = 2;
		selected = 1;
		engine->redrawDisplay();
	}
	if (iX >= 1080 && iX <= 1180 && iY >= 485 && iY <= 535) {
		gameSelection = 3;
		selected = 1;
		engine->redrawDisplay();
	}
	if (selected == 0) {
		gameSelection = -1;
		engine->redrawDisplay();
	}
}

void RunningState::reset() {
	engine->drawableObjectsChanged();
	engine->destroyOldObjects(true);
	string strFileName = "level" + to_string(currentLevel) + "Objects.txt";
	ifstream file;
	file.open(strFileName);
	if (!file) {
		cout << "Failed to open the file" << endl;
		exit(1);
	}

	int xPos;
	int yPos;
	int type;
	int index = 1;
	file >> currentNumBoxes;
	file >> xPos;
	file >> yPos;
	file >> type;
	mainX = xPos;
	mainY = yPos;

	engine->storeObjectInArray(0, new MainCharacter(engine, 360 + 40 * xPos, 155 + 40 * yPos, tm));
	engine->getDisplayableObject(0)->setShouldDeleteOnRemoval(true);
	file >> xPos;
	file >> yPos;
	file >> type;
	while (file) {
		if (type == 1) {
			engine->storeObjectInArray(index, new NormalBox(engine, 360 + 40 * xPos, 155 + 40 * yPos));
			engine->getDisplayableObject(index)->setShouldDeleteOnRemoval(true);
			file >> xPos;
			file >> yPos;
			file >> type;
			index++;
		}
		else if (type == 2) {
			engine->storeObjectInArray(index, new RedMonster(engine, 360 + 40 * xPos, 155 + 40 * yPos, tm));
			engine->getDisplayableObject(index)->setDefaultColour(2);
			engine->getDisplayableObject(index)->setShouldDeleteOnRemoval(true);
			file >> xPos;
			file >> yPos;
			file >> type;
			index++;
		}
		else if (type == 3) {
			engine->storeObjectInArray(index, new GreenMonster(engine, 360 + 40 * xPos, 155 + 40 * yPos, tm));
			engine->getDisplayableObject(index)->setDefaultColour(3);
			engine->getDisplayableObject(index)->setShouldDeleteOnRemoval(true);
			file >> xPos;
			file >> yPos;
			file >> type;
			index++;
		}
		else if (type == 4) {
			engine->storeObjectInArray(index, new BrownMonster(engine, 360 + 40 * xPos, 155 + 40 * yPos, tm));
			engine->getDisplayableObject(index)->setDefaultColour(4);
			engine->getDisplayableObject(index)->setShouldDeleteOnRemoval(true);
			file >> xPos;
			file >> yPos;
			file >> type;
			index++;
		}
	}
	//engine->storeObjectInArray(index, NULL);
	file.close();
	engine->redrawDisplay();
}

void RunningState::mouseDown(int iButton, int iX, int iY) {
	
	//If player clicks the "save" button
	if (iX >= 1080 && iX <= 1180 && iY >= 185 && iY <= 235) {
		ofstream file;
		file.open("currentSavedState.txt");
		file << currentScore << endl;
		file << currentTime << endl;
		file << currentLevel << endl;
		file << currentNumBoxes << endl;
		int i = 0;
		for (i; i <= currentNumBoxes; ++i) {				
			int xTile = tm->getMapXForScreenX(engine->getDisplayableObject(i)->getXCentre());
			int yTile = tm->getMapYForScreenY(engine->getDisplayableObject(i)->getYCentre());
			if (i == 0) {
				file << xTile << " " << yTile << " " << 0 <<endl;
			}
			else
				file << xTile << " " << yTile << " " << 1 << endl;					
		}
		while (engine->getDisplayableObject(i) != NULL) {
			if (engine->getDisplayableObject(i)->getDefaultColour() == 2) {
				int xTile = tm->getMapXForScreenX(engine->getDisplayableObject(i)->getXCentre());
				int yTile = tm->getMapYForScreenY(engine->getDisplayableObject(i)->getYCentre());
				file << xTile << " " << yTile << " " << 2 << endl;
				i++;
			}
			else if (engine->getDisplayableObject(i)->getDefaultColour() == 3) {
				int xTile = tm->getMapXForScreenX(engine->getDisplayableObject(i)->getXCentre());
				int yTile = tm->getMapYForScreenY(engine->getDisplayableObject(i)->getYCentre());
				file << xTile << " " << yTile << " " << 3 << endl;
				i++;
			}
			else if (engine->getDisplayableObject(i)->getDefaultColour() == 4) {
				int xTile = tm->getMapXForScreenX(engine->getDisplayableObject(i)->getXCentre());
				int yTile = tm->getMapYForScreenY(engine->getDisplayableObject(i)->getYCentre());
				if (engine->getDisplayableObject(i+1) == NULL)
					file << xTile << " " << yTile << " " << 4;
				else 
					file << xTile << " " << yTile << " " << 4 << endl;
				i++;
			}
		}
		file.close();
	}

	//If player clicks the "load" button
	if (iX >= 1080 && iX <= 1180 && iY >= 285 && iY <= 335) {	
		engine->drawableObjectsChanged();
		engine->destroyOldObjects(true);

		const char* strFileName = "currentSavedState.txt";
		ifstream file;
		file.open(strFileName);
		if (!file) {
			cout << "Failed to open the file" << endl;
			exit(1);
		}

		int xPos;
		int yPos;
		int type;
		int index = 1;

		file >> currentScore;
		file >> currentTime;	
		startPlayTime = engine->getModifiedTime() / 1000 - currentTime;

		file >> currentLevel;
		file >> currentNumBoxes;
		file >> xPos;
		file >> yPos;
		file >> type;
		
		for (int i = 0; i < 15; ++i) {
			for (int j = 0; j < 15; ++j) {
				tm->setMapValue(i, j, 0);
			}
		}

		tm->setMapValue(14, 0, 5);
		tm->setMapValue(13, 0, 1);
		tm->setMapValue(13, 1, 1);
		tm->setMapValue(14, 1, 1);

		tm->setMapValue(0, 7, 1);
		tm->setMapValue(1, 5, 1);
//		tm->setMapValue(1, 7, 1);
		tm->setMapValue(1, 9, 1);
//		tm->setMapValue(2, 5, 1);
//		tm->setMapValue(2, 9, 1);
//		tm->setMapValue(12, 4, 1);
//		tm->setMapValue(12, 8, 1);
		tm->setMapValue(13, 4, 1);
//		tm->setMapValue(13, 6, 1);
		tm->setMapValue(13, 8, 1);
		tm->setMapValue(14, 6, 1);
		tm->setMapValue(2, 12, 1);
		tm->setMapValue(3, 12, 1);
		tm->setMapValue(6, 12, 1);
		tm->setMapValue(8, 12, 1);
		tm->setMapValue(11, 12, 1);
		tm->setMapValue(12, 12, 1);

		//Load the corresponding map
		engine->lockAndSetupBackground();
		engine->redrawDisplay();
			
		mainX = xPos;
		mainY = yPos;
		//Load the corresponding objects;
		engine->storeObjectInArray(0, new MainCharacter(engine, 360 + 40 * xPos, 155 + 40 * yPos, tm));
		engine->getDisplayableObject(0)->setShouldDeleteOnRemoval(true);
		file >> xPos;
		file >> yPos;
		file >> type;
		while (file) {
			if (type == 1) {
				engine->storeObjectInArray(index, new NormalBox(engine, 360 + 40 * xPos, 155 + 40 * yPos));
				engine->getDisplayableObject(index)->setShouldDeleteOnRemoval(true);
				file >> xPos;
				file >> yPos;
				file >> type;
				index++;
			}
			else if (type == 2) {
				engine->storeObjectInArray(index, new RedMonster(engine, 360 + 40 * xPos, 155 + 40 * yPos, tm));
				engine->getDisplayableObject(index)->setDefaultColour(2);
				engine->getDisplayableObject(index)->setShouldDeleteOnRemoval(true);
				file >> xPos;
				file >> yPos;
				file >> type;
				index++;
			}
			else if (type == 3) {
				engine->storeObjectInArray(index, new GreenMonster(engine, 360 + 40 * xPos, 155 + 40 * yPos, tm));
				engine->getDisplayableObject(index)->setDefaultColour(3);
				engine->getDisplayableObject(index)->setShouldDeleteOnRemoval(true);
				file >> xPos;
				file >> yPos;
				file >> type;
				index++;
			}
			else if (type == 4) {
				engine->storeObjectInArray(index, new BrownMonster(engine, 360 + 40 * xPos, 155 + 40 * yPos, tm));
				engine->getDisplayableObject(index)->setDefaultColour(4);
				engine->getDisplayableObject(index)->setShouldDeleteOnRemoval(true);
				file >> xPos;
				file >> yPos;
				file >> type;
				index++;
			}
		}
	//	engine->storeObjectInArray(index, NULL);
		file.close();
		engine->redrawDisplay();
	}

	//If player clicks "reset" button
	if (iX >= 1080 && iX <= 1180 && iY >= 385 && iY <= 435) {
		reset();
	}

	//If player clicks "Quit" button
	if (iX >= 1080 && iX <= 1180 && iY >= 485 && iY <= 535) {
		engine->setExitWithCode(0);
	}
}

void RunningState::playMusic() {
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	Mix_Music *sound = Mix_LoadMUS("gameMusic.mp3");
	Mix_PlayMusic(sound, 10);
	//SDL_Delay(1000);  
}

void RunningState::keyDown(int iKeyCode) {	
	switch (iKeyCode)
	{
		case SDLK_SPACE: 					
			engine->pause();
			Scyxw3CW4Engine::bs = Scyxw3CW4Engine::pauseState;	
			//engine->lockAndSetupBackground();
			engine->redrawDisplay();			
			break;	
	}
}

void RunningState::drawStringsOnTop()
{
	// Build the string to print
	char buf[128];
	currentTime = engine->getModifiedTime() / 1000 - startPlayTime;

	sprintf(buf, "Time %3d", currentTime);
	engine->drawForegroundString(engine->getWindowWidth() - 230, 100, buf, 0x66ffcc, NULL);
}

void RunningState::virtMainLoopDoBeforeUpdate() {
	//++m_iOffset;
	//m_iOffset = (m_iOffset + 1) % (engine->getWindowHeight()); 
	//virtSetupBackgroundBuffer(); 
	//engine->redrawDisplay();
}

void RunningState::copyAllBackgroundBuffer() {
	(engine->getForegroundSurface())->copyRectangleFrom(engine->getBackgroundSurface(), 0, 0, engine->getWindowWidth(), engine->getWindowHeight(), 0, m_iOffset);
	(engine->getForegroundSurface())->copyRectangleFrom(engine->getBackgroundSurface(), 0, engine->getWindowHeight() - m_iOffset, engine->getWindowWidth(), engine->getWindowHeight(), 0, m_iOffset - engine->getWindowHeight());
	//	m_pForegroundSurface->copyRectangleFrom(m_pBackgroundSurface, 0, 0, getWindowWidth(), getWindowHeight(), 0, m_iOffset);
	//	m_pForegroundSurface->copyRectangleFrom(m_pBackgroundSurface, 0, getWindowHeight() - m_iOffset, getWindowWidth(), getWindowHeight(), 0, m_iOffset - getWindowHeight());
}
