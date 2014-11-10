#include "HumanPlayer.h"
#include "HumanGameGrid.h"
#include <string>
#include <stdlib.h>

using namespace Matrix;


HumanPlayer::HumanPlayer(string name)
{
	this->userName = name;
}


HumanPlayer::~HumanPlayer(void)
{

}

bool HumanPlayer::DidIWin(GameGrid* gameGrid)
{
	unsigned int counter = 0;

	for(unsigned int i = 0; i < Boats::ROW_SIZE; i++)
	{
		for(unsigned int j = 0; j < Boats::ROW_SIZE; j++)
		{
			if(gameGrid->getSquareNumber(i, j) != 0 && gameGrid->getSquareCheck(i, j) == true)
			{
				counter++;
			}
		}
	}

	if(counter == 17)
	{
		return true;
	}
	else
		return false;
}

string HumanPlayer::GetName()
{
	return this->userName;
}