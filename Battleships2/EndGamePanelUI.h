#pragma once
#include "DialogUI.h"
#include "MenuUI.h"
#include "../GamePlay/PlayGame.h"
#include "SFML/Graphics.hpp"

#define DEFAULT_SPLASHSCREEN_HEIGHT 350
#define DEFAULT_SPLASHSCREEN_WIDTH 800


using namespace sf;

class EndGamePanelUI
{
public:
	EndGamePanelUI(void);
	EndGamePanelUI(bool isWinner);
	~EndGamePanelUI(void);
private:
	RenderWindow* endGameWindow;
	Text gagne;
	Text perdu;
	MenuUI* newGameButton;
	MenuUI* quitButton;
	Font font;
	void CreateMessage(bool isWinner);
	void ManageEventLoop();
};

