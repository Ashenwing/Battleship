#include "NewGameUI.h"
#include "GameUI.h"

#include <iostream>

NewGameUI::NewGameUI()
{
	newGameWindow = new RenderWindow(VideoMode(800, 350, 32), "BATTLESHIPS 2.0");
	newGameWindow->setVerticalSyncEnabled(true);

	CreateNewGameMenu();
	createTitle();
	ManageEventLoop();
}

NewGameUI::~NewGameUI(void)
{
	delete easyButton;
	delete hardButton;
	delete newGameWindow;
}

void NewGameUI::CreateNewGameMenu()
{
	easyButton = new MenuUI("PARTIE DE PÊCHE", 100, 175);
	hardButton = new MenuUI("SEEK & DESTROY", 500, 175);

	easyButton->DisplayTextAtPosition(*newGameWindow);
	hardButton->DisplayTextAtPosition(*newGameWindow);
}

void NewGameUI::createTitle()
{
	if (font.loadFromFile("../images/stencil.ttf"))
	{
		title.setFont(font);
		title.setString("BATTLESHIPS 2.0");
		title.setCharacterSize(TITLE_FONT_SIZE);
		title.setColor(HARD_FONT_COLOR);
		title.setPosition((newGameWindow->getSize().x/2) - (title.getLocalBounds().width/2), 10);
		newGameWindow->draw(title);
	}
}

void NewGameUI::ManageEventLoop()
{
	newGameWindow->display();
	newGameWindow->clear();

	while (newGameWindow->isOpen())
	{
		Event event;
		while (newGameWindow->pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				newGameWindow->close();
			}
			else if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left)
			{
				if (easyButton->CheckClickPosition(event.mouseButton.x, event.mouseButton.y))
				{
					PlayGame::gameLevel = 1;
				}
				else if (hardButton->CheckClickPosition(event.mouseButton.x, event.mouseButton.y))
				{
					PlayGame::gameLevel = 2;
				}
				SetupBoatsUI setupBoatsScreen;
				newGameWindow->close();
			}
		}
	}
	
}