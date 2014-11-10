#pragma once
#include "SFML/Graphics.hpp"
#include "MenuUI.h"
#include "SetupBoatsUI.h"
#include "../GamePlay/PlayGame.h"

#define DEFAULT_FONT_SIZE 24
#define TITLE_FONT_SIZE 80
#define EASY_FONT_COLOR sf::Color::Cyan
#define HARD_FONT_COLOR sf::Color::Red


class NewGameUI
{
public:
	NewGameUI();
	~NewGameUI(void);

	void CreateNewGameMenu();
	void ManageEventLoop();
private:
	MenuUI* easyButton;
	MenuUI* hardButton;
	Font font;
	Text title;
	RenderWindow* newGameWindow;
	void createTitle();
};

