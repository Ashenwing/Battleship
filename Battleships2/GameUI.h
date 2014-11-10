#pragma once
#include "SFML/Graphics.hpp"
#include "GridUI.h"
#include "MenuUI.h"
#include "../GamePlay/Tile.h"
#include "../GamePlay/PlayGame.h"

/*	Cette classe appelle tous les éléments du GUI
	Author: Annie Belzile
*/
class GameUI
{
public:
	GameUI();
	GameUI(vector<Tile*>& humanGrid);
	~GameUI();

	vector<Tile*>& GetHumanGrid();
	void CreateGameMainMenu();
	void CreateEnemyGrid();
	void CreatePlayerGrid();
	void PollUIEvents();
	void AIEventLoop();
	RenderWindow* GetGameWindow();
	
private:
	PlayGame* game;
	vector<Tile*> grid;
	vector<Tile*> pcGrid;
	RenderWindow* gameWindow;
	Event* event;
	GridUI* enemyGrid;
	GridUI* playerGrid;
	MenuUI* quitButton;
	MenuUI* newGameButton;
	MenuUI* saveProfileButton;
	DialogUI* nomHuman;
	DialogUI* nomComputer;
	int mouseX;
	int mouseY;
	void ShowBoats();
};

