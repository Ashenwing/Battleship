#include "ComputerGameGrid.h"
#include "Boats.h"
#include <cassert>

using namespace Matrix;

ComputerGameGrid::ComputerGameGrid(void)
{
	SetGameGrid();
}

ComputerGameGrid::~ComputerGameGrid(void)
{
	vector<Tile*>::iterator deleter = this->computerVector.begin();

	for(; deleter < computerVector.end(); deleter++)
	{
		delete *deleter;
	}
	computerVector.clear();	
}

int ComputerGameGrid::Size()
{
	return this->computerVector.size();
}
void ComputerGameGrid::SetGameGrid()
{
	for(unsigned int i = 0; i < Boats::ROW_SIZE * Boats::ROW_SIZE; i++)
	{
		Tile* newTile = new Tile(0, false, "");
		computerVector.push_back(newTile);
	}

	assert(this->Size() != 0);
}

vector<Tile*> ComputerGameGrid::getGameVector()
{
	return this->computerVector;
}

//Vérifie si les positions désirées sont dans la grille.
bool ComputerGameGrid::CheckSpace(unsigned int boatSize, bool direction, unsigned int x, unsigned int y, vector<Tile*> gameGrid)
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

	if(validSpace == true)
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


//Vérfie si les cases du bateau rentre dans la grille.
bool ComputerGameGrid::QuickCheck(unsigned int i, unsigned int j, unsigned int boatSize, vector<Tile*> gameGrid)
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


//Pour transformer un Array[][] en Array[], la formule est:
// (x * row_size + y)
int ComputerGameGrid::getSquareNumber(unsigned int x, unsigned int y)
{
	return this->computerVector.at(x * Boats::ROW_SIZE + y)->getNumber();
}
bool ComputerGameGrid::getSquareCheck(unsigned int x, unsigned int y)
{
	return this->computerVector.at(x * Boats::ROW_SIZE + y)->isClicked();
}
string ComputerGameGrid::getSquareName(unsigned int x, unsigned int y)
{
	return this->computerVector.at(x * Boats::ROW_SIZE + y)->getName();
}
void ComputerGameGrid::setSquareCheck(unsigned int x, unsigned int y, bool check)
{
	this->computerVector.at(x * Boats::ROW_SIZE + y)->setClicked(check);
}
void ComputerGameGrid::setSquareContent(unsigned int x, unsigned int y, unsigned int boatSize, string boatName)
{
	this->computerVector.at(x * Boats::ROW_SIZE + y)->setNumber(boatSize);
	this->computerVector.at(x * Boats::ROW_SIZE + y)->setName(boatName);
	this->computerVector.at(x * Boats::ROW_SIZE + y)->setClicked(false);

}