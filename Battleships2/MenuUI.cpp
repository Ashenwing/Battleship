#include "MenuUI.h"


MenuUI::MenuUI(void)
{
}

MenuUI::MenuUI(string text, float x, float y)
{
	this->text = text;
	this->posX = x;
	this->posY = y;
}


MenuUI::~MenuUI(void)
{
}



void MenuUI::DisplayTextAtPosition(RenderWindow& target)
{
	if (loadFont())
	{
		createText();
	}
	displayText.setPosition(posX, posY);
	target.draw(displayText);
}

Text& MenuUI::GetButton()
{
	return displayText;
}

float& MenuUI::GetPosX()
{
	return this->posX;
}

float& MenuUI::GetPosY()
{
	return this->posY;
}


bool MenuUI::CheckClickPosition(int mousePosX, int mousePosY)
{
	if (mousePosX > this->posX && mousePosX < (this->posX + displayText.getLocalBounds().width))
	 {
        if (mousePosY > this->posY && mousePosY < (this->posY + displayText.getLocalBounds().height))
		{
			return true;
		}
	 }
	 return false;
}

bool MenuUI::loadFont()
{
	if (!font.loadFromFile("../images/arial.ttf"))
	{
		return false;
	}
	return true;
}

void MenuUI::createText()
{
	displayText.setFont(font); 
	displayText.setString(this->text);
	displayText.setCharacterSize(DEFAULT_FONT_SIZE);
	displayText.setColor(DEFAULT_FONT_COLOR);
}

