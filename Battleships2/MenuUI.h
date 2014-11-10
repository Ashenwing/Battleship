#pragma once
#include "SFML/Graphics.hpp"

using namespace sf;
using namespace std;

#define DEFAULT_FONT_SIZE 24
#define DEFAULT_FONT_COLOR sf::Color::Cyan

/* Cette classe génère tous les éléments de texte avec lesquels le joueur
	doit interagir.
	Author: Annie Belzile
*/
class MenuUI
{
public:
	MenuUI(void);
	MenuUI(string text, float x, float y);
	~MenuUI(void);

	void DisplayTextAtPosition(RenderWindow& target);
	bool CheckClickPosition(int mousePosX, int mousePosY);
	Text& GetButton();
	float& GetPosX();
	float& GetPosY();

private:
	Font font;
	Text displayText;
	string text;
	float posX;
	float posY;
	bool loadFont();
	void createText();
};

