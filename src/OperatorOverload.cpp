#include "OperatorOverload.h"

int OperatorOverload::operator -- () {
	//Find the minimum value among x, y, j and k, and 
	//Return the corresponding direction choice (Operator Overloading)
	int newChoice = 0;
	int min = x;	

	if (y < min) {
		min = y;
		newChoice = 1;
	}
	if (j < min) {
		min = j;
		newChoice = 2;
	}
	if (k < min) {
		min = k;
		newChoice = 3;
	}
	
	return newChoice;
}

void OperatorOverload::setX(int x) {
	this->x = x;
}
void OperatorOverload::setY(int y) {
	this->y = y;
}
void OperatorOverload::setJ(int j) {
	this->j = j;
}
void OperatorOverload::setK(int k) {
	this->k = k;
}