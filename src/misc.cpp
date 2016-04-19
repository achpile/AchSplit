/***********************************************************************
     * File       : misc.cpp
     * Created    : Apr 17, 2016
     * Copyright  : (C) 2016 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "headers.hpp"



/***********************************************************************
     * createWindow

***********************************************************************/
void createWindow() {
	app = new sf::RenderWindow(sf::VideoMode(settings->getWidth(), settings->getHeight(), 32),
	                           CAPTION VERSION);

	app->setPosition(settings->getPosition());
}



/***********************************************************************
     * createText

***********************************************************************/
void createText(sf::Text **text, sf::Font *font, int size, sf::Vector2f pos, sf::Color color, const char *caption) {
	(*text) = new sf::Text;

	(*text)->setFont(*font);
	(*text)->setCharacterSize(size);
	(*text)->setPosition(pos);
	(*text)->setFillColor(color);
	(*text)->setString(caption);
}



/***********************************************************************
     * min

***********************************************************************/
int min(int a, int b) {
	return (a < b) ? a : b;
}



/***********************************************************************
     * bound

***********************************************************************/
int bound(int x, int a, int b) {
	if (b < a) return a;
	if (x < a) return a;
	if (x > b) return b;

	return x;
}
