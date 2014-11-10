#include "HumanGameGrid.h"
#include "../Battleships2/SetupBoatsUI.h"
#include "Boats.h"
#include <cassert>

using namespace Matrix;

HumanGameGrid::HumanGameGrid(void)
{
}

HumanGameGrid::HumanGameGrid(vector<Tile*> playerGrid)
{
	this->playerVector = playerGrid;
}

HumanGameGrid::~HumanGameGrid(void)
{
	assert(playerVector.size() > 0);

	vector<Tile*>::iterator deleter = this->playerVector.begin();

	for(; deleter < playerVector.end(); deleter++)
	{
		delete *deleter;
	}
	playerVector.clear();
}

int HumanGameGrid::Size()
{
	return this->playerVector.size();
}

void HumanGameGrid::SetGameGrid(vector<Tile*>& humanGrid)
{
	this->playerVector = humanGrid;
}


vector<Tile*> HumanGameGrid::getGameVector()
{
	return this->playerVector;
}

bool HumanGameGrid::CheckSpace(unsigned int boatSize, bool direction, unsigned int x, unsigned int y, vector<Tile*> gameGrid)
{
	bool validSpace = true;

	if(x + boatSize > Boats::ROW_SIZE -1)
	{
		validSpace = false;
	}
	if(y + boatSize > Boats::ROW_SIZE -1)
	{
		validSpace = false;
	}

	if(validSpace)
	{
		if(direction) // si verticale
		{
			validSpace = QuickCheck(x, y, boatSize, gameGrid);
		}
		else // si horizontale
		{
			validSpace = QuickCheck(y, x, boatSize, gameGrid);
		}
	}
	return validSpace;
}

bool HumanGameGrid::QuickCheck(unsigned int i, unsigned int j, unsigned int boatSize, vector<Tile*> gameGrid)
{
	bool valid = true;

	for(unsigned int space = i; space < i + boatSize; space++)
    {
        if(valid)
        {
            if(gameGrid.at(space * Boats::ROW_SIZE + j)->getNumber() != 0)
            {
                    valid = false;
            }
        }
		else
		{
			space = i + boatSize;
		}
    }
	return valid;
}
int HumanGameGrid::getSquareNumber(unsigned int x, unsigned int y)
{
	return this->playerVector.at(x * Boats::ROW_SIZE + y)->getNumber();
}
bool HumanGameGrid::getSquareCheck(unsigned int x, unsigned int y)
{
	return this->playerVector.at(x * Boats::ROW_SIZE + y)->isClicked();
}
void HumanGameGrid::setSquareCheck(unsigned int x, unsigned int y, bool check)
{
	this->playerVector.at(x * Boats::ROW_SIZE + y)->setClicked(check);
}
string HumanGameGrid::getSquareName(unsigned int x, unsigned int y)
{
	return this->playerVector.at(x * Boats::ROW_SIZE + y)->getName();
}
void HumanGameGrid::setSquareContent(unsigned int x, unsigned int y, unsigned int boatSize, string boatName)
{
	this->playerVector.at(x * Boats::ROW_SIZE + y)->setNumber(boatSize);
	this->playerVector.at(x * Boats::ROW_SIZE + y)->setName(boatName);
	this->playerVector.at(x * Boats::ROW_SIZE + y)->setClicked(false);
}