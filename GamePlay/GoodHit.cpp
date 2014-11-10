#include "GoodHit.h"


GoodHit::GoodHit(int x, int y, string boatName, int direction)
{
	this->x = x;
	this->y = y;
	this->name = boatName;
	this->shotDirection = direction;
}


GoodHit::~GoodHit(void)
{
}

string GoodHit::getName() { return this->name;}
int GoodHit::getX() { return this->x;}
int GoodHit::getY() { return this->y;}
int GoodHit::getShotDirection() { return this->shotDirection;}