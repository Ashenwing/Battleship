#include "DialogUI.h"

#define DEFAULT_DIALOG_FONT_SIZE 24

DialogUI::DialogUI(void)
{
}

DialogUI::DialogUI(sf::RenderWindow& target, std::string text, float posX, float posY)
{
	this->text.setString(text);
	this->x = posX;
	this->y = posY;
	CreateDialog(target);
}


DialogUI::~DialogUI(void)
{
}

void DialogUI::CreateDialog(sf::RenderWindow& target)
{
	if (font.loadFromFile("../images/arial.ttf"))
	{
		text.setFont(font);
		text.setCharacterSize(DEFAULT_DIALOG_FONT_SIZE);
		text.setColor(sf::Color::Red);
		text.setPosition(this->x, this->y);
		target.draw(text);
	}
}

void DialogUI::Update(sf::RenderWindow& target)
{
	target.draw(text);
}

sf::Text& DialogUI::GetText()
{
	return text;
}

