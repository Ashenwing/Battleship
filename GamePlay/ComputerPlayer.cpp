#include "ComputerPlayer.h"
#include "ComputerGameGrid.h"
#include "GoodHit.h"
#include <string>
#include <stdlib.h>
#include <time.h>
#include "../Battleships2/EndGamePanelUI.h"

using namespace Matrix;


ComputerPlayer::ComputerPlayer() 
{

}

ComputerPlayer::ComputerPlayer(string name)
{
	this->userName = name;
}

ComputerPlayer::~ComputerPlayer(void)
{
	for(vector<GoodHit*>::iterator deleter = goodHits.begin(); deleter < goodHits.end(); deleter++)
	{
		delete *deleter;
	}
	goodHits.clear();
}

void ComputerPlayer::SetBoats(GameGrid* gameGrid, bool direction, int boatSize, string boatName)
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

bool ComputerPlayer::ShootEnemy(GameGrid* gameGrid)
{
	srand(time(NULL));

	bool shotFired = false;
	bool didIHitABoat = false;
	unsigned int vecSize = 0;

	if(goodHits.empty())
	{
		RandomShot(gameGrid);
		if(vecSize != goodHits.size())
		{
			didIHitABoat = true;
		}
	}
	else
	{

		int lastTileX = goodHits.back()->getX(); //pour faciliter la lecture
		int lastTileY = goodHits.back()->getY();
		int shotDirection = goodHits.back()->getShotDirection();

		while(!shotFired)
		{
			switch (shotDirection)
			{
			case 0: //en haut
				{
					vecSize = goodHits.size();
					if(lastTileX - 1 >= 0 && Attack(lastTileX - 1, lastTileY, *gameGrid, shotDirection))
					{
						shotFired = true;

						if(vecSize != goodHits.size())
							didIHitABoat = true;
					}
					else
					{
						if(goodHits.size() == 1)
						{
							shotDirection = rand() % 4;
						}
						else
						{
							if(CheckMultipleBoatX(*gameGrid))
							{
								shotDirection = "13"[rand() %2] - 48;
							}
							else
							{
								shotDirection = 2;
							}
							lastTileX = goodHits.at(0)->getX();
							lastTileY = goodHits.at(0)->getY();
						}
					}
					break;
				}
			case 1: // A droite
				{
					vecSize = goodHits.size();
					if(lastTileY + 1 < 11 && Attack(lastTileX, lastTileY + 1, *gameGrid, shotDirection))
					{
						shotFired = true;

						if(vecSize != goodHits.size())
							didIHitABoat = true;
					}
					else
					{
						if(goodHits.size() == 1)
						{
							shotDirection = rand() % 4;
						}
						else
						{
							if(CheckMultipleBoatY(*gameGrid))
							{
								shotDirection = "02"[rand() %2] - 48;
							}
							else
							{
								shotDirection = 3;
							}
							lastTileX = goodHits.at(0)->getX();
							lastTileY = goodHits.at(0)->getY();
						}
					}
					break;
				}
			case 2: //en bas
				{
					vecSize = goodHits.size();
					if(lastTileX + 1 < 11 && Attack(lastTileX + 1, lastTileY, *gameGrid, shotDirection))
					{
						shotFired = true;

						if(vecSize != goodHits.size())
							didIHitABoat = true;
					}
					else
					{
						if(goodHits.size() == 1)
						{
							shotDirection = rand() % 4;
						}
						else
						{
							if(CheckMultipleBoatX(*gameGrid))
							{
								shotDirection = "13"[rand() %2] - 48;	
							}
							else
							{
								shotDirection = 0;
							}
							lastTileX = goodHits.at(0)->getX();
							lastTileY = goodHits.at(0)->getY();
						}
					}
					break;
				}
			case 3: // a gauche
				{
					vecSize = goodHits.size();
					if(lastTileY - 1 >= 0 && Attack(lastTileX, lastTileY - 1, *gameGrid, shotDirection))
					{
						shotFired = true;

						if(vecSize != goodHits.size())
							didIHitABoat = true;
					}
					else
					{
						if(goodHits.size() == 1)
						{
							shotDirection = rand() % 4;
						}
						else
						{
							if(CheckMultipleBoatY(*gameGrid))
							{
								shotDirection = "02"[rand() %2] - 48;
							}
							else
							{
								shotDirection = 1;
							}
							lastTileX = goodHits.at(0)->getX();
							lastTileY = goodHits.at(0)->getY();
						}
					}
					break;
				}
			}
		}
	}
	return didIHitABoat;
}	

void ComputerPlayer::RandomShot(GameGrid* gameGrid)
{
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
		BoatHit(randomX, randomY, gameGrid->getSquareName(randomX, randomY), rand() % 4);
		
	}
}
void ComputerPlayer::BoatHit(int x, int y, string boatName, int direction)
{
	GoodHit* shot = new GoodHit(x, y, boatName, direction);
	goodHits.push_back(shot);
}

bool ComputerPlayer::Attack(int x, int y, GameGrid& gameGrid, int shotDirection)
{
	if(gameGrid.getSquareCheck(x, y) == false)
	{
		gameGrid.setSquareCheck(x, y, true);

		if(gameGrid.getSquareNumber(x, y) != 0)
		{
			BoatHit(x, y, gameGrid.getSquareName(x, y), shotDirection);
			IsBoatDestroyed(gameGrid.getSquareName(x, y), &gameGrid);
		}
		return true;
	}
	else
		return false;
}


//Vérifiée lorsque on à frappé l'eau des deux cotés du bateaux sans l'avoir coulé.
//Ceci indique que chaque case frappé fait partie d'un bateau différent.
bool ComputerPlayer::CheckMultipleBoatX(GameGrid& gameGrid)
{
	if(gameGrid.getSquareCheck(goodHits.at(0)->getX() + 1, goodHits.at(0)->getY()) == true
	&& gameGrid.getSquareCheck(goodHits.at(0)->getX() - 1, goodHits.at(0)->getY()) == true)
	{
		return true;
	}
	else
		return false;

}

bool ComputerPlayer::CheckMultipleBoatY(GameGrid& gameGrid)
{
	if(gameGrid.getSquareCheck(goodHits.at(0)->getX(), goodHits.at(0)->getY() + 1) == true
	&& gameGrid.getSquareCheck(goodHits.at(0)->getX(), goodHits.at(0)->getY() - 1) == true)
	{
		return true;
	}
	else
		return false;

}

bool ComputerPlayer::IsBoatDestroyed(string name, GameGrid* gameGrid)
{
	unsigned int hitCounter = 0;

	for(unsigned int i = 0; i < goodHits.size(); i++)
	{
		if(goodHits.at(i)->getName() == name)
		{
			hitCounter++;
		}
	}

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

void ComputerPlayer::RemoveBoat(string name)
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


vector<GoodHit*> ComputerPlayer::getVec()
{
	return this->goodHits;
}
 
bool ComputerPlayer::DidIWin(GameGrid* gameGrid)
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

string ComputerPlayer::GetName()
{
	return this->userName;
}



//Cette fonction est seulement utilisé par les tests. La différence, c'est qu'au lieu
// d'utiliser la GameGrid propre au Player (sa variable membre), il le recoit en paramètre.
void ComputerPlayer::ShootEnemyTest(GameGrid* gameGrid, vector<GoodHit*>& goodHits)
{
	srand(time(NULL));

	bool shotFired = false;
	bool didIHitABoat = false;
	unsigned int vecSize = 0;

	if(goodHits.empty())
	{
		RandomShot(gameGrid);
	}
	else
	{
		int lastTileX = goodHits.back()->getX(); //pour faciliter la lecture
		int lastTileY = goodHits.back()->getY();
		int shotDirection = goodHits.back()->getShotDirection();

		while(!shotFired)
		{
			switch (shotDirection)
			{
			case 0: //en haut
				{
					vecSize = goodHits.size();
					if(lastTileX - 1 >= 0 && Attack(lastTileX - 1, lastTileY, *gameGrid, shotDirection))
					{
						shotFired = true;

						if(vecSize != goodHits.size())
							didIHitABoat = true;
					}
					else
					{
						if(goodHits.size() == 1)
						{
							shotDirection = rand() % 4;
						}
						else
						{
							if(CheckMultipleBoatX(*gameGrid))
							{
								shotDirection = "13"[rand() %2] - 48;
							}
							else
							{
								shotDirection = 2;
							}
							lastTileX = goodHits.at(0)->getX();
							lastTileY = goodHits.at(0)->getY();
						}
					}
					break;
				}
			case 1: // A droite
				{
					vecSize = goodHits.size();
					if(lastTileY + 1 < 11 && Attack(lastTileX, lastTileY + 1, *gameGrid, shotDirection))
					{
						shotFired = true;

						if(vecSize != goodHits.size())
							didIHitABoat = true;
					}
					else
					{
						if(goodHits.size() == 1)
						{
							shotDirection = rand() % 4;
						}
						else
						{
							if(CheckMultipleBoatY(*gameGrid))
							{
								shotDirection = "02"[rand() %2] - 48;
							}
							else
							{
								shotDirection = 3;
							}
							lastTileX = goodHits.at(0)->getX();
							lastTileY = goodHits.at(0)->getY();
						}
					}
					break;
				}
			case 2: //en bas
				{
					vecSize = goodHits.size();
					if(lastTileX + 1 < 11 && Attack(lastTileX + 1, lastTileY, *gameGrid, shotDirection))
					{
						shotFired = true;

						if(vecSize != goodHits.size())
							didIHitABoat = true;
					}
					else
					{
						if(goodHits.size() == 1)
						{
							shotDirection = rand() % 4;
						}
						else
						{
							if(CheckMultipleBoatX(*gameGrid))
							{
								shotDirection = "13"[rand() %2] - 48;	
							}
							else
							{
								shotDirection = 0;
							}
							lastTileX = goodHits.at(0)->getX();
							lastTileY = goodHits.at(0)->getY();
						}
					}
					break;
				}
			case 3: // a gauche
				{
					vecSize = goodHits.size();
					if(lastTileY - 1 >= 0 && Attack(lastTileX, lastTileY - 1, *gameGrid, shotDirection))
					{
						shotFired = true;

						if(vecSize != goodHits.size())
							didIHitABoat = true;
					}
					else
					{
						if(goodHits.size() == 1)
						{
							shotDirection = rand() % 4;
						}
						else
						{
							if(CheckMultipleBoatY(*gameGrid))
							{
								shotDirection = "02"[rand() %2] - 48;
							}
							else
							{
								shotDirection = 1;
							}
							lastTileX = goodHits.at(0)->getX();
							lastTileY = goodHits.at(0)->getY();
						}
					}
					break;
				}
			}
		}
	}
}	