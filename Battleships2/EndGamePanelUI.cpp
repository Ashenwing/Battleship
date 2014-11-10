#include "EndGamePanelUI.h"


EndGamePanelUI::EndGamePanelUI()
{
}

EndGamePanelUI::EndGamePanelUI(bool isWinner)
{
	endGameWindow = new RenderWindow(VideoMode(400, 150, 32), "FIN DE LA PARTIE!");
	endGameWindow->setVerticalSyncEnabled(true);
	CreateMessage(isWinner);
	clock_t goal = 4000 + clock(); //Délai
	while (goal > clock()); 
}


EndGamePanelUI::~EndGamePanelUI()
{
	delete endGameWindow;
}

void EndGamePanelUI::CreateMessage(bool isWinner)
{
	if (font.loadFromFile("../images/stencil.ttf"))
	{
		if (isWinner)
		{
			gagne.setString("VICTOIRE!");
			gagne.setFont(font);
			gagne.setCharacterSize(80);
			gagne.setColor(Color::Cyan);
			gagne.setPosition((endGameWindow->getSize().x/2) - (gagne.getLocalBounds().width/2), 25);
			endGameWindow->draw(gagne);
		}
	else
		{
			perdu.setString("PERDU!");
			perdu.setFont(font);
			perdu.setCharacterSize(80);
			perdu.setColor(Color::Red);
			perdu.setPosition((endGameWindow->getSize().x/2) - (perdu.getLocalBounds().width/2), 25);
			endGameWindow->draw(perdu);
		}
	}
	endGameWindow->display();
	endGameWindow->clear();
}

//void EndGamePanelUI::ManageEventLoop()
//{
//	endGameWindow->display();
//	endGameWindow->clear();
//
//	while (endGameWindow->isOpen())
//	{
//		Event event;
//		while (endGameWindow->pollEvent(event))
//		{
//			if (event.type == Event::Closed)
//			{
//				endGameWindow->close();
//			}
//			else if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left)
//			{
//				if (newGameButton->CheckClickPosition(event.mouseButton.x, event.mouseButton.y))
//				{
//					endGameWindow->close();
//					PlayGame newGame;
//				}
//				else if (quitButton->CheckClickPosition(event.mouseButton.x, event.mouseButton.y))
//				{
//					endGameWindow->close();
//				}
//			}
//		}
//	}
//}
