#include "GameUI.h"
#include "NewGameUI.h"
#include "EndGamePanelUI.h"
#include "../PlayerProfile/PlayerProfile.h"
#include <iostream> //DEBUG

GameUI::GameUI(vector<Tile*>& humanGrid)
{
	this->gameWindow = new RenderWindow(VideoMode(1200, 800, 32), "BATTLESHIPS 2.0");
	this->gameWindow->setVerticalSyncEnabled(true);
	CreateGameMainMenu();
	CreateEnemyGrid();
	CreatePlayerGrid();
	game = new PlayGame();
	game->Start();
	grid = humanGrid;
	game->getHumanGrid()->SetGameGrid(humanGrid);

	pcGrid = game->getComputerGrid()->getGameVector();
	
	PollUIEvents();
}

GameUI::~GameUI()
{
	delete nomComputer;
	delete nomHuman;
	delete quitButton;
	delete newGameButton;
	delete saveProfileButton;
	delete enemyGrid;
	delete playerGrid;
	delete gameWindow;
	delete event;
	delete game;
}

vector<Tile*>& GameUI::GetHumanGrid()
{
	return this->grid;
}

RenderWindow* GameUI::GetGameWindow()
{
	return this->gameWindow;
}

void GameUI::CreateGameMainMenu()
{
	quitButton = new MenuUI("QUITTER", 1000, 10); 
	newGameButton = new MenuUI("NOUVELLE PARTIE", 200, 10);
	saveProfileButton = new MenuUI("SAUVEGARDER LE PROFIL", 550, 10);

	quitButton->DisplayTextAtPosition(*gameWindow);
	newGameButton->DisplayTextAtPosition(*gameWindow);
	saveProfileButton->DisplayTextAtPosition(*gameWindow);
}

void GameUI::CreateEnemyGrid()
{
	enemyGrid = new GridUI();
	enemyGrid->CreateGrid(*gameWindow, 150, 150);

	
}

void GameUI::CreatePlayerGrid()
{
	playerGrid = new GridUI();
	playerGrid->CreateGrid(*gameWindow, 650, 150);
}

void GameUI::ShowBoats()
{
	for (unsigned int i = 0; i < grid.size(); i++)
	{
		if (grid[i]->getNumber() != 0)
		{
			mouseX = i / TILE_NUMBER;
			mouseY = i % TILE_NUMBER;
			playerGrid->GetSprite(mouseX, mouseY)->setTexture(playerGrid->GetBoatTile());
			playerGrid->UpdateGrid(*gameWindow);
		}
	}

}

void GameUI::PollUIEvents()
{

	ShowBoats();
	nomHuman = new DialogUI(*gameWindow, game->getHuman()->GetName(), 800, 560);
	nomComputer = new DialogUI(*gameWindow, game->getComputer()->GetName(), 300, 560);
	gameWindow->display();
	gameWindow->clear();
	event = new Event();
	while (gameWindow->isOpen())
	{
		while (gameWindow->pollEvent(*event))
		{
			if (event->type == Event::Closed)
			{
				gameWindow->close();
			}
			else if (event->type == Event::MouseButtonReleased && event->mouseButton.button == Mouse::Left)
			{
				mouseX = Mouse::getPosition(*gameWindow).x;
				mouseY = Mouse::getPosition(*gameWindow).y;
				int X = enemyGrid->GetTabMatrixCoordinatesX(mouseX, mouseY);
				int Y = enemyGrid->GetTabMatrixCoordinatesY(mouseX, mouseY);

				if (quitButton->CheckClickPosition(mouseX, mouseY))
				{
					gameWindow->close();
				}
				else if (newGameButton->CheckClickPosition(mouseX, mouseY))
				{
					gameWindow->close();
					NewGameUI newGame;
				}
				else if (saveProfileButton->CheckClickPosition(mouseX, mouseY))
				{
					PlayerProfile saveGame(*game->getHumanGrid());
					if(saveGame.Save())
					{
						DialogUI saveGameSuccess(*gameWindow,"Reussi!", 550, 35);
					}
					else
					{
						DialogUI saveGameSuccess(*gameWindow,"Echec!", 550, 35);
					}
					enemyGrid->UpdateGrid(*gameWindow);
					playerGrid->UpdateGrid(*gameWindow);
					quitButton->DisplayTextAtPosition(*gameWindow);
					newGameButton->DisplayTextAtPosition(*gameWindow);
					saveProfileButton->DisplayTextAtPosition(*gameWindow);
					nomComputer->Update(*gameWindow);
					nomHuman->Update(*gameWindow);
					gameWindow->display();
					gameWindow->clear();
				}
				if ((mouseX >=150 && mouseX <=550) && (mouseY >=150 && mouseY <=550) && game->getComputerGrid()->getGameVector().at(X * 10 + Y)->isClicked() == false)
				{
					if (game->getComputerGrid()->getGameVector().at(X * 10 + Y)->getNumber() == 0)
					{
						enemyGrid->GetSpriteAtPosition(mouseX, mouseY)->setTexture(enemyGrid->GetMissedTile());
						game->getComputerGrid()->getGameVector().at(X * 10 + Y)->setClicked(true);
						AIEventLoop();
						enemyGrid->UpdateGrid(*gameWindow);
						playerGrid->UpdateGrid(*gameWindow);
						quitButton->DisplayTextAtPosition(*gameWindow);
						newGameButton->DisplayTextAtPosition(*gameWindow);
						saveProfileButton->DisplayTextAtPosition(*gameWindow);
						nomComputer->Update(*gameWindow);
						nomHuman->Update(*gameWindow);
						gameWindow->display();
						gameWindow->clear();
					}
					else 
					{
						enemyGrid->GetSpriteAtPosition(mouseX, mouseY)->setTexture(enemyGrid->GetHitTile());
						game->getComputerGrid()->getGameVector().at(X * 10 + Y)->setClicked(true);
						enemyGrid->UpdateGrid(*gameWindow);
						playerGrid->UpdateGrid(*gameWindow);
						quitButton->DisplayTextAtPosition(*gameWindow);
						newGameButton->DisplayTextAtPosition(*gameWindow);
						saveProfileButton->DisplayTextAtPosition(*gameWindow);
						nomComputer->Update(*gameWindow);
						nomHuman->Update(*gameWindow);
						gameWindow->display();
						gameWindow->clear();
					}
					if (game->getHuman()->DidIWin(game->getComputerGrid()))
					{
						gameWindow->close();
						EndGamePanelUI endGame(game->getHuman()->DidIWin(game->getComputerGrid()));
						
					}
				}
			}
		}
	}
	
}

void GameUI::AIEventLoop()
{
	bool pcTry = false;
	do
	{
		pcTry = game->getComputer()->ShootEnemy(game->getHumanGrid());
	}
	while(pcTry == true);
	playerGrid->ResetHitGrid(*gameWindow, game->getHumanGrid()->getGameVector());
	enemyGrid->UpdateGrid(*gameWindow);
	playerGrid->UpdateGrid(*gameWindow);
	quitButton->DisplayTextAtPosition(*gameWindow);
	newGameButton->DisplayTextAtPosition(*gameWindow);
	saveProfileButton->DisplayTextAtPosition(*gameWindow);
	nomComputer->Update(*gameWindow);
	nomHuman->Update(*gameWindow);

	gameWindow->display();
	gameWindow->clear();
	
}