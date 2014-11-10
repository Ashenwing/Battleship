#include "ComputerPlayerExpert.h"
#include "../Battleships2/EndGamePanelUI.h"
#include <cassert>



ComputerPlayerExpert::ComputerPlayerExpert(string name, GameGrid* humanGrid)
{
	this->userName = name;
	this->cheatGrid = humanGrid;
}

ComputerPlayerExpert::~ComputerPlayerExpert(void)
{
	for(vector<GoodHit*>::iterator deleter = goodHits.begin(); deleter < goodHits.end(); deleter++)
	{
		delete *deleter;
	}
	goodHits.clear();
}

void ComputerPlayerExpert::SetBoats(GameGrid* gameGrid, bool direction, int boatSize, string boatName)
{
	srand (time(NULL));

	int randomX = 0;
	int randomY = 0;

	do
	{
		randomX = rand() % 10;
		randomY = rand() % 10;
	}
	while(!gameGrid->CheckSpace(boatSize, direction, randomX, randomY,gameGrid->getGameVector()));

	if(direction) //si verticale
    { 
            for(int x = randomX; x < randomX + boatSize; x++) 
            {
                    gameGrid->setSquareContent(x, randomY, boatSize, boatName);  
            }
    } 
    else 
    { // si horizontale
            for(int y = randomY; y < randomY + boatSize; y++) 
            {
                    gameGrid->setSquareContent(y, randomX, boatSize, boatName);
            }
    }   
}


//Il ne rentre jamais dans cette fonction, et c'est à cause de GameUI qui appelle
//celui de ComputerPlayer. C'est la même chose que ShootEnemy de ComputerPlayer,
//mais plus efficace.
bool ComputerPlayerExpert::ShootEnemy(GameGrid* gameGrid)
{
	assert(gameGrid->Size() != 0);
	bool didIHitABoat = false;

	if(goodHits.empty())
	{
		RandomShot(gameGrid);
		if(goodHits.size() != 0)
		{
			didIHitABoat = true;
		}
	}
	else
	{
		int lastTileX = goodHits.back()->getX(); //pour faciliter la lecture
		int lastTileY = goodHits.back()->getY();
		int shotDirection = goodHits.back()->getShotDirection();
		 
		switch (shotDirection)
		{
		case 0: //en haut
			{
				if( lastTileX -1 >= 0)
				{
					Attack(lastTileX - 1, lastTileY, *gameGrid);
					didIHitABoat = true;
					break;
				}
			}
		case 1: // A droite
			{
				if( lastTileY +1 < 11)
				{
					Attack(lastTileX, lastTileY + 1, *gameGrid);
					didIHitABoat = true;
					break;
				}
			}
		case 2: //en bas
			{
				if( lastTileX + 1 < 11)
				{
					Attack(lastTileX + 1, lastTileY, *gameGrid);
					didIHitABoat = true;				
					break;
				}
			}
		case 3: // a gauche
			{
				if( lastTileY -1 >= 0)
				{
					Attack(lastTileX, lastTileY - 1, *gameGrid);
					didIHitABoat = true;
					break;
				}
			}
		}
	}
	return didIHitABoat;
}

void ComputerPlayerExpert::RandomShot(GameGrid* gameGrid)
{
	srand(time(NULL));

	int randomX = 0;
	int randomY = 0;

	do
	{
		randomX = rand() % 10;
		randomY = rand() % 10;
	}
	while(gameGrid->getSquareCheck(randomX, randomY) == true);

	gameGrid->setSquareCheck(randomX, randomY, true);

	if(gameGrid->getSquareNumber(randomX, randomY) != 0)
	{
		BoatHit(randomX, randomY, gameGrid->getSquareName(randomX, randomY));
	}

}

void ComputerPlayerExpert::Attack(int x, int y, GameGrid& gameGrid)
{
	gameGrid.setSquareCheck(x, y, true);
	BoatHit(x, y, gameGrid.getSquareName(x, y));
	IsBoatDestroyed(gameGrid.getSquareName(x, y), &gameGrid);
}

void ComputerPlayerExpert::BoatHit(int x, int y, string boatName)
{
	int shotDirection = 0;

	//Le computer vérifie ou se trouve la prochaine case du bateau en question.
	if(x - 1 >= 0 && this->cheatGrid->getSquareName(x - 1, y) == boatName && 
		this->cheatGrid->getSquareCheck(x - 1, y) == false)
	{
		shotDirection = 0;
	}
	else
	{
		if(x + 1 < 11 && this->cheatGrid->getSquareName(x + 1, y) == boatName && 
			this->cheatGrid->getSquareCheck(x + 1, y) == false)
		{
			shotDirection = 2;
		}
		else
		{
			if(y + 1 < 11 && this->cheatGrid->getSquareName(x, y + 1) == boatName && 
				this->cheatGrid->getSquareCheck(x, y + 1) == false)
			{
				shotDirection = 1;
			}
			else
			{
				if(y - 1 >= 0 && this->cheatGrid->getSquareName(x, y - 1) == boatName && 
					this->cheatGrid->getSquareCheck(x, y - 1) == false)
				{
					shotDirection = 3;
				}
			}
		}
	}
	GoodHit* newShot = new GoodHit(x, y, boatName, shotDirection);
	this->goodHits.push_back(newShot);
}

bool ComputerPlayerExpert::IsBoatDestroyed(string name, GameGrid* gameGrid)
{
	unsigned int hitCounter = 0;

	for(unsigned int i = 0; i < goodHits.size(); i++)
	{
		if(goodHits.at(i)->getName() == name)
		{
			hitCounter++;
		}
	}

	//Si le nombre de coups correspond au nombre de cases que contient le bateau.
	if(hitCounter == name.back() - 48)
	{
		RemoveBoat(name);

		if(DidIWin(gameGrid))
		{
			EndGamePanelUI endGame(false);
		}
	}
	else
	{
		return false;
	}
}

void ComputerPlayerExpert::RemoveBoat(string name)
{
	if(goodHits.size() == name.back() - 48)
	{
		goodHits.clear();
	}
	else
	{
		vector<GoodHit*>::iterator deleter = goodHits.begin();

		int counter = 0;

		while(deleter != goodHits.end() - 1)
		{
			if(goodHits.at(counter)->getName() == name)
			{
				goodHits.erase(deleter);	
			}
			else
			{
				counter++;
			}
			deleter = goodHits.begin() + counter;
		}
		delete *deleter;
	}
}
bool ComputerPlayerExpert::DidIWin(GameGrid* gameGrid)
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

vector<GoodHit*> ComputerPlayerExpert::getVec()
{
	return this->goodHits;
}

string ComputerPlayerExpert::GetName()
{
	return this->userName;
}