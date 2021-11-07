#include "header.h"
#include "BoxObject.h"
#include "Scyxw3CW4Engine.h"

BoxObject::BoxObject(BaseEngine* pEngine, int x, int y) : DisplayableObject(pEngine)
{
	m_iCurrentScreenX = x;
	m_iCurrentScreenY = y;
}

BoxObject::~BoxObject() {
}

void BoxObject::virtDraw() {
}

void BoxObject::virtDoUpdate(int iCurrentTime) {
}