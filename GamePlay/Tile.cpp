#include "Tile.h"
#include <string>
#include <cassert>


Tile::Tile(void)
{
}


Tile::~Tile(void)
{
}

Tile::Tile(int tileNumber, bool check, string boatName)
{
	assert(tileNumber >= 0 && tileNumber < 6);

	this->clicked = check;
	this->tileNumber = tileNumber;
	this->name = boatName;
}

int Tile::getNumber(){return this->tileNumber;}
string Tile::getName(){return this->name;}
bool Tile::isClicked(){return this->clicked;}

void Tile::setName(string boatName)
{
	this->name = boatName;
}

void Tile::setClicked(bool check)
{
	this->clicked = check;
}

void Tile::setNumber(int number)
{
	this->tileNumber = number;
}