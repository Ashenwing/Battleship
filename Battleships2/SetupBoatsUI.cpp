#include "SetupBoatsUI.h"
#include "../GamePlay/Boats.h"
#include "GameUI.h"
#include <ctime>

using namespace Boats;

SetupBoatsUI::SetupBoatsUI()
{
	this->setupWindow = new RenderWindow(VideoMode(1200, 800, 32), "BATTLESHIPS 2.0");
	this->setupWindow->setVerticalSyncEnabled(true);
	CreateSetupGrid();
}

SetupBoatsUI::~SetupBoatsUI(void)
{
	delete event;
	delete title;
	delete instructions;
	delete error;
	delete setupGrid;
	delete setupWindow;
}

void SetupBoatsUI::CreateSetupGrid()
{
	setupGrid = new GridUI();
	setupGrid->CreateGrid(*setupWindow, 400, 200);
	for (int i = 0; i < TILE_NUMBER; i++)
	{
		for (int j = 0; j < TILE_NUMBER; j++)
		{
			matrixBoats[i][j] = 0;
		}
	}
	title = new DialogUI(*setupWindow, "DÉPLOYEZ VOS NAVIRES!", 400, 50);
	instructions = new DialogUI(*setupWindow, "Dans l'ordre:\n- Porte-avions (5 cases)\n- Cuirassé (4 cases)\n- Torpilleur (3 cases)\n- Sous-marin (3 cases)\n- Patrouille (2 cases)", 50, 300);
	ManageEventLoop();
}

bool SetupBoatsUI::ValidateBoatMatrix()
{
	bool isValid = false;
	vector<int> array5;
	vector<int> array4;
	vector<int> array3;
	vector<int> array2;
	vector<int> array1;
	for (int x = 0; x < TILE_NUMBER; x++)
	{
		for (int y = 0; y < TILE_NUMBER; y++)
		{
			if (matrixBoats[x][y] != 0)
			{
				switch (matrixBoats[x][y])
				{
				case 5:
					array5.push_back(x);
					array5.push_back(y);
					break;
				case 4:
					array4.push_back(x);
					array4.push_back(y);
					break;
				case 3:
					array3.push_back(x);
					array3.push_back(y);
					break;
				case 2:
					array2.push_back(x);
					array2.push_back(y);
					break;
				case 1:
					array1.push_back(x);
					array1.push_back(y);
					break;
				default:
					break;
				}
			}
		}
	}
	if (areTilesContiguous(array5) && areTilesContiguous(array4) && areTilesContiguous(array3) && areTilesContiguous(array2) && areTilesContiguous(array1))
	{
		return true;
	}
	else 
	{
		return false;
	}
}

void SetupBoatsUI::ManageEventLoop()
{
	setupWindow->display();
	setupWindow->clear();
	event = new Event();
	bool ready = false;
	MenuUI start("DÉMARRER LA PARTIE", 500, 700);
	nbrClicksRemaining = 17;
	while (setupWindow->isOpen())
	{
		while (setupWindow->pollEvent(*event))
		{
			if (event->type == Event::Closed)
			{
				setupWindow->close();
			}
			else if (event->type == Event::MouseButtonReleased && event->mouseButton.button == Mouse::Left && nbrClicksRemaining > 0)
			{
				mouseX = Mouse::getPosition(*setupWindow).x;
				mouseY = Mouse::getPosition(*setupWindow).y;
				
				if ((mouseX >=400 && mouseX <=800) && (mouseY >=200 && mouseY <=600) &&
					matrixBoats[setupGrid->GetTabMatrixCoordinatesX(mouseX, mouseY)][setupGrid->GetTabMatrixCoordinatesY(mouseX, mouseY)] == 0)
				{
					setupGrid->GetSpriteAtPosition(mouseX, mouseY)->setTexture(setupGrid->GetBoatTile());
					setupGrid->UpdateGrid(*setupWindow);
					title->Update(*setupWindow);
					instructions->Update(*setupWindow);
					setupWindow->display();
					setupWindow->clear();
					

					if (nbrClicksRemaining > 12 && matrixBoats[setupGrid->GetTabMatrixCoordinatesX(mouseX, mouseY)][setupGrid->GetTabMatrixCoordinatesY(mouseX, mouseY)] == 0)
					{
						nbrClicksRemaining--;
						matrixBoats[setupGrid->GetTabMatrixCoordinatesX(mouseX, mouseY)][setupGrid->GetTabMatrixCoordinatesY(mouseX, mouseY)] = 5;
						ready = false;
					}
					else if (nbrClicksRemaining > 8 && matrixBoats[setupGrid->GetTabMatrixCoordinatesX(mouseX, mouseY)][setupGrid->GetTabMatrixCoordinatesY(mouseX, mouseY)] == 0)
					{
						nbrClicksRemaining--;
						matrixBoats[setupGrid->GetTabMatrixCoordinatesX(mouseX, mouseY)][setupGrid->GetTabMatrixCoordinatesY(mouseX, mouseY)] = 4;
						ready = false;
					}
					else if (nbrClicksRemaining > 5 && matrixBoats[setupGrid->GetTabMatrixCoordinatesX(mouseX, mouseY)][setupGrid->GetTabMatrixCoordinatesY(mouseX, mouseY)] == 0)
					{
						nbrClicksRemaining--;
						matrixBoats[setupGrid->GetTabMatrixCoordinatesX(mouseX, mouseY)][setupGrid->GetTabMatrixCoordinatesY(mouseX, mouseY)] = 3;
						ready = false;
					}
					else if (nbrClicksRemaining > 2 && matrixBoats[setupGrid->GetTabMatrixCoordinatesX(mouseX, mouseY)][setupGrid->GetTabMatrixCoordinatesY(mouseX, mouseY)] == 0)
					{
						nbrClicksRemaining--;
						matrixBoats[setupGrid->GetTabMatrixCoordinatesX(mouseX, mouseY)][setupGrid->GetTabMatrixCoordinatesY(mouseX, mouseY)] = 2;
						ready = false;
					}
					else if (nbrClicksRemaining > 0 && matrixBoats[setupGrid->GetTabMatrixCoordinatesX(mouseX, mouseY)][setupGrid->GetTabMatrixCoordinatesY(mouseX, mouseY)] == 0)
					{
						nbrClicksRemaining--;
						matrixBoats[setupGrid->GetTabMatrixCoordinatesX(mouseX, mouseY)][setupGrid->GetTabMatrixCoordinatesY(mouseX, mouseY)] = 1;
						ready = true;
					}
					else if (matrixBoats[setupGrid->GetTabMatrixCoordinatesX(mouseX, mouseY)][setupGrid->GetTabMatrixCoordinatesY(mouseX, mouseY)] != 0)
					{
						nbrClicksRemaining++;
					}
					if (ready || nbrClicksRemaining == 0)
					{
						start.DisplayTextAtPosition(*setupWindow);
					}
				}
			}
			else if (event->type == Event::MouseButtonReleased && event->mouseButton.button == Mouse::Left && nbrClicksRemaining == 0)
			{
				mouseX = Mouse::getPosition(*setupWindow).x;
				mouseY = Mouse::getPosition(*setupWindow).y;
				if (start.CheckClickPosition(mouseX, mouseY))
				{
					if(ValidateBoatMatrix())
					{
						ConvertBoatsMatrix();
						setupWindow->close();
						GameUI gameUI(humanGrid);
					}
					else
					{
						error = new DialogUI(*setupWindow, "DISPOSITION IMPOSSIBLE!", 400, 60);
						setupWindow->display();
						setupWindow->clear();
						clock_t goal = 2000 + clock(); //Délai
						while (goal > clock()); 
						ResetGrid();
					}
				}
			}
		}
	}
} 

bool SetupBoatsUI::areTilesContiguous(vector<int>& tileArray)
{
	bool vertical = false;
	bool horizontal = false;
	bool contiguous = false;
	vector<int> evenValue;
	vector<int> oddValue;

	unsigned int max = tileArray.size();
	for (unsigned int i = 0; i < max; i++)
	{
		if (i % 2 == 0)
		{
			evenValue.push_back(tileArray[i]);
		}
		else
		{
			oddValue.push_back(tileArray[i]);
		}
	}
	int firsteven = evenValue[0];
	for (unsigned int i = 0; i < evenValue.size(); i++)
	{
		
		if (firsteven == evenValue[i])
		{
			horizontal = true;
		}
		else
		{
			horizontal = false;
		}
	}
	int firstodd = oddValue[0];
	for (unsigned int i = 0; i < oddValue.size(); i++)
	{
		
		if (firstodd == oddValue[i])
		{
			vertical = true;
		}
		else
		{
			vertical = false;
		}
	}

	if (horizontal)
	{
		for (unsigned int i = 0; i < oddValue.size(); i++)
		{
			if (firstodd == oddValue[i]-i)
			{
				contiguous = true;
			}
			else
			{
				contiguous = false;
			}
		}
	}
	else if (vertical)
	{
		for (unsigned int i = 0; i < evenValue.size(); i++)
		{
			if (firsteven == evenValue[i]-i)
			{
				contiguous = true;
			}
			else
			{
				contiguous = false;
			}
		}
	}

	if ((vertical && contiguous) || (horizontal && contiguous))
	{
		return true;
	}
	else
	{
		return false;
	}
}

GridUI& SetupBoatsUI::GetGrid()
{
	return *setupGrid;
}

void SetupBoatsUI::ResetGrid() 
{
	nbrClicksRemaining = 17;
	setupGrid->ResetEmptyGrid();
	setupGrid->UpdateGrid(*setupWindow);

	for (int i = 0; i < TILE_NUMBER; i++)
	{
		for (int j = 0; j < TILE_NUMBER; j++)
		{
			matrixBoats[i][j] = 0;
		}
	}
	title->Update(*setupWindow);
	instructions->Update(*setupWindow);
	setupWindow->display();
	setupWindow->clear();
}

void SetupBoatsUI::ConvertBoatsMatrix()
{
	for (int x = 0; x < TILE_NUMBER; x++)
	{
		for (int y = 0; y < TILE_NUMBER; y++)
		{
			Tile* newTile = new Tile(0, false, "");
			humanGrid.push_back(newTile);
		}
	}
	for (int x = 0; x < TILE_NUMBER; x++)
	{
		for (int y = 0; y < TILE_NUMBER; y++)
		{
			switch (matrixBoats[x][y])
				{
				case 5:
					this->humanGrid.at(x * TILE_NUMBER + y)->setNumber(5);
					this->humanGrid.at(x * TILE_NUMBER + y)->setName(STR_AIRCRAFT);
					this->humanGrid.at(x * TILE_NUMBER + y)->setClicked(false);
					break;
				case 4:
					this->humanGrid.at(x * TILE_NUMBER + y)->setNumber(4);
					this->humanGrid.at(x * TILE_NUMBER + y)->setName(STR_BATTLESHIP);
					this->humanGrid.at(x * TILE_NUMBER + y)->setClicked(false);
					break;
				case 3:
					this->humanGrid.at(x * TILE_NUMBER + y)->setNumber(3);
					this->humanGrid.at(x * TILE_NUMBER + y)->setName(STR_DESTROYER);
					this->humanGrid.at(x * TILE_NUMBER + y)->setClicked(false);
					break;
				case 2:
					this->humanGrid.at(x * TILE_NUMBER + y)->setNumber(3);
					this->humanGrid.at(x * TILE_NUMBER + y)->setName(STR_SUBMARINE);
					this->humanGrid.at(x * TILE_NUMBER + y)->setClicked(false);
					break;
				case 1:
					this->humanGrid.at(x * TILE_NUMBER + y)->setNumber(2);
					this->humanGrid.at(x * TILE_NUMBER + y)->setName(STR_PATROL);
					this->humanGrid.at(x * TILE_NUMBER + y)->setClicked(false);
					break;
				default:
					break;
			}
		}
	}
}