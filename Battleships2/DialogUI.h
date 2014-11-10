#pragma once
#include "SFML/Graphics.hpp"

/*	Cette classe sert à afficher du texte statique (messages)
	Author: Annie Belzile
*/
class DialogUI
{
public:
	DialogUI(void);
	DialogUI(sf::RenderWindow& target, std::string text, float posX, float posY);
	~DialogUI(void);
	void Update(sf::RenderWindow& target);
	sf::Text& GetText();

private:
	void CreateDialog(sf::RenderWindow& target);
	sf::Font font;
	sf::Text text;
	float x;
	float y;
};

