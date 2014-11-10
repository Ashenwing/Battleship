#pragma once
#include "GridUI.h"
#include "MenuUI.h"
#include "DialogUI.h"
#include "../GamePlay/Tile.h"
#include "../GamePlay/HumanGameGrid.h"
#include "SFML/Graphics.hpp"

using namespace sf;

/*	Cette classe créé une interface permettant au joueur de placer ses bateaux sur la grille
	Author: Annie Belzile
*/
class SetupBoatsUI
{
public:
	SetupBoatsUI(void);
	~SetupBoatsUI(void);

	void ManageEventLoop();
	void CreateSetupGrid();
	GridUI& GetGrid();
	void ResetGrid();
	bool validGrid;
	void ConvertBoatsMatrix();
	vector<Tile*> GetVector();

private:
	RenderWindow* setupWindow;
	GridUI* setupGrid;
	Event* event;
	DialogUI* title;
	DialogUI* instructions;
	DialogUI* error;
	vector<Tile*> humanGrid;
	int matrixBoats[TILE_NUMBER][TILE_NUMBER];
	int nbrClicksRemaining;
	int mouseX;
	int mouseY;

	bool ValidateBoatMatrix();
	bool areTilesContiguous(vector<int>& tileArray);
};

